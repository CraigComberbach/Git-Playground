#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#if defined(_MSC_VER)
	#define BREAKPOINT() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
	#if defined(__arm__) || defined(__thumb__) || defined(__aarch64__)
		//ARM or ARM64 architecture
		#define BREAKPOINT() __asm volatile("bkpt #0")
	#else
		//x86/x64 architecture
		#define BREAKPOINT() __asm__ __volatile__("int3")
	#endif
#else
	#error "Unsupported compiler"
#endif

#define BREAKPOINT_IF_TRUE(condition) \
	if(condition) BREAKPOINT();

#endif//BREAKPOINT_H
