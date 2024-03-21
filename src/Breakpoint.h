#ifndef BREAKPOINT_H
#define BREAKPOINT_H

/**
 * This header provides macros for triggering breakpoints in debug builds.
 * BREAKPOINT() triggers an unconditional breakpoint.
 * BREAKPOINT_IF_TRUE(condition) triggers a breakpoint if the condition evaluates to true.
 *
 * These macros are designed to be no-ops in release builds (when NDEBUG is defined).
 * They support x86/x64, ARM/ARM64, MIPS, and PowerPC architectures with GCC, Clang, and MSVC compilers.
 * Unsupported compilers or architectures will generate a warning, and the macros will degrade gracefully.
 */

//Only define the breakpoint macros if NDEBUG is not defined (debug mode)
#ifndef NDEBUG
	#if defined(_MSC_VER)
		#define BREAKPOINT() __debugbreak()
	#elif defined(__GNUC__) || defined(__clang__)
		#if defined(__arm__) || defined(__thumb__) || defined(__aarch64__)
			//ARM or ARM64 architecture
			#define BREAKPOINT() __asm volatile("bkpt #0")
		#elif defined(__mips__)
			//MIPS architecture
			#define BREAKPOINT() __asm volatile("break")
		#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
			//PowerPC architecture
			#define BREAKPOINT() __asm volatile("twge r2, r2")
		#else
			//x86/x64 architecture
			#define BREAKPOINT() __asm__ __volatile__("int3")
		#endif
	#else
		//Generate a warning for unsupported compilers, but allow compilation to proceed
		#warning "The Breakpoint library does not support this compiler or architecture."
		//Define BREAKPOINT as a no-op to prevent compilation errors
		#define BREAKPOINT() ((void)0)
	#endif
	#define BREAKPOINT_IF_TRUE(condition) \
		if(condition) BREAKPOINT();
#else
	//Define empty macros if in release mode (NDEBUG defined)
	#define BREAKPOINT()				  ((void)0)
	#define BREAKPOINT_IF_TRUE(condition) ((void)0)
#endif//NDEBUG

#endif//BREAKPOINT_H
