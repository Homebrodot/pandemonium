import os
import platform
import sys
from methods import get_compiler_version, using_gcc

# This file is mostly based on platform/x11/detect.py.
# If editing this file, make sure to apply relevant changes here too.


def is_active():
    return True


def get_name():
    return "Server"


def get_program_suffix():
    if sys.platform == "darwin":
        return "osx"
    return "x11"


def can_build():
    if os.name != "posix":
        return False

    return True


def get_opts():
    from SCons.Variables import BoolVariable, EnumVariable

    return [
        EnumVariable("linker", "Linker program", "default", ("default", "bfd", "gold", "lld", "mold")),
        BoolVariable("use_llvm", "Use the LLVM compiler", False),
        BoolVariable("use_static_cpp", "Link libgcc and libstdc++ statically for better portability", True),
        BoolVariable('use_coverage', 'Test Pandemonium coverage', False),
        BoolVariable("use_ubsan", "Use LLVM/GCC compiler undefined behavior sanitizer (UBSAN)", False),
        BoolVariable("use_asan", "Use LLVM/GCC compiler address sanitizer (ASAN))", False),
        BoolVariable("use_lsan", "Use LLVM/GCC compiler leak sanitizer (LSAN))", False),
        BoolVariable("use_tsan", "Use LLVM/GCC compiler thread sanitizer (TSAN))", False),
        BoolVariable("debug_symbols", "Add debugging symbols to release/release_debug builds", True),
        BoolVariable("use_msan", "Use LLVM/GCC compiler memory sanitizer (MSAN))", False),
        BoolVariable("separate_debug_symbols", "Create a separate file containing debugging symbols", False),
        BoolVariable("execinfo", "Use libexecinfo on systems where glibc is not available", False),
    ]


def get_flags():
    return []


def configure(env):
    ## Build type

    if env["target"] == "release":
        if env["optimize"] == "speed":  # optimize for speed (default)
            env.Prepend(CCFLAGS=["-O3"])
        elif env["optimize"] == "size":  # optimize for size
            env.Prepend(CCFLAGS=["-Os"])

        if env["debug_symbols"]:
            env.Prepend(CCFLAGS=["-g2"])

    elif env["target"] == "release_debug":
        if env["optimize"] == "speed":  # optimize for speed (default)
            env.Prepend(CCFLAGS=["-O2"])
        elif env["optimize"] == "size":  # optimize for size
            env.Prepend(CCFLAGS=["-Os"])

        if env["debug_symbols"]:
            env.Prepend(CCFLAGS=["-g2"])

    elif env["target"] == "debug":
        env.Prepend(CCFLAGS=["-g3"])
        env.Append(LINKFLAGS=["-rdynamic"])

    if env["debug_symbols"]:
        # Adding dwarf-4 explicitly makes stacktraces work with clang builds,
        # otherwise addr2line doesn't understand them
        env.Append(CCFLAGS=["-gdwarf-4"])

    ## Architecture

    # Cross-compilation
    # TODO: Support cross-compilation on architectures other than x86.
    host_is_64_bit = sys.maxsize > 2**32
    if env["bits"] == "default":
        env["bits"] = "64" if host_is_64_bit else "32"
    if host_is_64_bit and (env["bits"] == "32" or env["arch"] == "x86"):
        env.Append(CCFLAGS=["-m32"])
        env.Append(LINKFLAGS=["-m32"])
    elif not host_is_64_bit and (env["bits"] == "64" or env["arch"] == "x86_64"):
        env.Append(CCFLAGS=["-m64"])
        env.Append(LINKFLAGS=["-m64"])

    if env["arch"] == "" and platform.machine() == "riscv64":
        env["arch"] = "rv64"

    if env["arch"] == "rv64":
        # G = General-purpose extensions, C = Compression extension (very common).
        env.Append(CCFLAGS=["-march=rv64gc"])

    ## Compiler configuration

    if "CXX" in env and "clang" in os.path.basename(env["CXX"]):
        # Convenience check to enforce the use_llvm overrides when CXX is clang(++)
        env["use_llvm"] = True

    if env["use_llvm"]:
        if "clang++" not in os.path.basename(env["CXX"]):
            env["CC"] = "clang"
            env["CXX"] = "clang++"
        env.extra_suffix = ".llvm" + env.extra_suffix
        env.Append(LIBS=["atomic"])

    # Linker
    if env["linker"] != "default":
        print("Using linker program: " + env["linker"])
        if env["linker"] == "mold" and using_gcc(env):  # GCC < 12.1 doesn't support -fuse-ld=mold.
            cc_semver = tuple(get_compiler_version(env))
            if cc_semver < (12, 1):
                found_wrapper = False
                for path in ["/usr/libexec", "/usr/local/libexec", "/usr/lib", "/usr/local/lib"]:
                    if os.path.isfile(path + "/mold/ld"):
                        env.Append(LINKFLAGS=["-B" + path + "/mold"])
                        found_wrapper = True
                        break
                if not found_wrapper:
                    print("Couldn't locate mold installation path. Make sure it's installed in /usr or /usr/local.")
                    sys.exit(255)
            else:
                env.Append(LINKFLAGS=["-fuse-ld=mold"])
        else:
            env.Append(LINKFLAGS=["-fuse-ld=%s" % env["linker"]])

    if env['use_coverage']:
        env.Append(CCFLAGS=['-ftest-coverage', '-fprofile-arcs'])
        env.Append(LINKFLAGS=['-ftest-coverage', '-fprofile-arcs'])

    # Sanitizers
    if env["use_ubsan"] or env["use_asan"] or env["use_lsan"] or env["use_tsan"] or env["use_msan"]:
        env.extra_suffix += "s"

        if env["use_ubsan"]:
            env.Append(CCFLAGS=["-fsanitize=undefined"])
            env.Append(LINKFLAGS=["-fsanitize=undefined"])

        if env["use_asan"]:
            env.Append(CCFLAGS=["-fsanitize=address"])
            env.Append(LINKFLAGS=["-fsanitize=address"])

        if env["use_lsan"]:
            env.Append(CCFLAGS=["-fsanitize=leak"])
            env.Append(LINKFLAGS=["-fsanitize=leak"])

        if env["use_tsan"]:
            env.Append(CCFLAGS=["-fsanitize=thread"])
            env.Append(LINKFLAGS=["-fsanitize=thread"])

        if env["use_msan"]:
            env.Append(CCFLAGS=["-fsanitize=memory"])
            env.Append(LINKFLAGS=["-fsanitize=memory"])

    # LTO
    if env["lto"] != "none":
        if env["lto"] == "thin":
            if not env["use_llvm"]:
                print("ThinLTO is only compatible with LLVM, use `use_llvm=yes` or `lto=full`.")
                sys.exit(255)
            env.Append(CCFLAGS=["-flto=thin"])
            env.Append(LINKFLAGS=["-flto=thin"])
        elif not env["use_llvm"] and env.GetOption("num_jobs") > 1:
            env.Append(CCFLAGS=["-flto"])
            env.Append(LINKFLAGS=["-flto=" + str(env.GetOption("num_jobs"))])
        else:
            env.Append(CCFLAGS=["-flto"])
            env.Append(LINKFLAGS=["-flto"])

        if not env["use_llvm"]:
            env["RANLIB"] = "gcc-ranlib"
            env["AR"] = "gcc-ar"

    env.Append(CCFLAGS=["-pipe"])

    ## Dependencies

    # FIXME: Check for existence of the libs before parsing their flags with pkg-config

    # freetype depends on libpng and zlib, so bundling one of them while keeping others
    # as shared libraries leads to weird issues
    if env["builtin_freetype"] or env["builtin_libpng"] or env["builtin_zlib"]:
        env["builtin_freetype"] = True
        env["builtin_libpng"] = True
        env["builtin_zlib"] = True

    if not env["builtin_freetype"]:
        env.ParseConfig("pkg-config freetype2 --cflags --libs")

    if not env["builtin_libpng"]:
        env.ParseConfig("pkg-config libpng16 --cflags --libs")

    if False:  # not env['builtin_assimp']:
        # FIXME: Add min version check
        env.ParseConfig("pkg-config assimp --cflags --libs")

    if not env["builtin_enet"]:
        env.ParseConfig("pkg-config libenet --cflags --libs")

    if not env["builtin_squish"]:
        env.ParseConfig("pkg-config libsquish --cflags --libs")

    if not env["builtin_zstd"]:
        env.ParseConfig("pkg-config libzstd --cflags --libs")

    # Sound and video libraries
    # Keep the order as it triggers chained dependencies (ogg needed by others, etc.)

    if not env["builtin_libtheora"]:
        env["builtin_libogg"] = False  # Needed to link against system libtheora
        env["builtin_libvorbis"] = False  # Needed to link against system libtheora
        env.ParseConfig("pkg-config theora theoradec --cflags --libs")
    else:
        list_of_x86 = ["x86_64", "x86", "i386", "i586"]
        if any(platform.machine() in s for s in list_of_x86):
            env["x86_libtheora_opt_gcc"] = True

    if not env["builtin_libvorbis"]:
        env["builtin_libogg"] = False  # Needed to link against system libvorbis
        env.ParseConfig("pkg-config vorbis vorbisfile --cflags --libs")

    if not env["builtin_opus"]:
        env["builtin_libogg"] = False  # Needed to link against system opus
        env.ParseConfig("pkg-config opus opusfile --cflags --libs")

    if not env["builtin_libogg"]:
        env.ParseConfig("pkg-config ogg --cflags --libs")

    if not env["builtin_mbedtls"]:
        # mbedTLS does not provide a pkgconfig config yet. See https://github.com/ARMmbed/mbedtls/issues/228
        env.Append(LIBS=["mbedtls", "mbedcrypto", "mbedx509"])

    if not env["builtin_wslay"]:
        env.ParseConfig("pkg-config libwslay --cflags --libs")

    if not env["builtin_miniupnpc"]:
        # No pkgconfig file so far, hardcode default paths.
        env.Prepend(CPPPATH=["/usr/include/miniupnpc"])
        env.Append(LIBS=["miniupnpc"])

    # On Linux wchar_t should be 32-bits
    # 16-bit library shouldn't be required due to compiler optimisations
    if not env["builtin_pcre2"]:
        env.ParseConfig("pkg-config libpcre2-32 --cflags --libs")

    ## Flags

    # Linkflags below this line should typically stay the last ones
    if not env["builtin_zlib"]:
        env.ParseConfig("pkg-config zlib --cflags --libs")

    env.Prepend(CPPPATH=["#platform/server"])
    env.Append(CPPDEFINES=["SERVER_ENABLED", "UNIX_ENABLED"])

    if platform.system() == "Darwin":
        env.Append(LINKFLAGS=["-framework", "Cocoa", "-framework", "Carbon", "-lz", "-framework", "IOKit"])

    env.Append(LIBS=["pthread"])

    if platform.system() == "Linux":
        env.Append(LIBS=["dl"])

    if platform.system().find("BSD") >= 0:
        env["execinfo"] = True

    if env["execinfo"]:
        env.Append(LIBS=["execinfo"])

    if platform.system() != "Darwin":
        # Link those statically for portability
        if env["use_static_cpp"]:
            env.Append(LINKFLAGS=["-static-libgcc", "-static-libstdc++"])
            if env["use_llvm"] and platform.system() != "FreeBSD":
                #env["LINKCOM"] = env["LINKCOM"] + " -l:libatomic.a"
                env["LINKCOM"] = env["LINKCOM"] + " -latomic"
        else:
            if env["use_llvm"] and platform.system() != "FreeBSD":
                env.Append(LIBS=["atomic"])
