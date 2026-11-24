/* Experiment 15: Conditional Compilation Using ifdef and ifndef
 * Input: No input. Define LAB_FEATURE=0 at compilation to disable the feature.
 */
#include "lab.h"
#ifndef LAB_FEATURE
#define LAB_FEATURE 1
#endif
#ifndef LAB_FALLBACK
#define LAB_FALLBACK 42
#endif

int main(void)
{
#ifdef LAB_FEATURE
#if LAB_FEATURE
    puts("Feature enabled");
#else
    puts("Feature disabled");
#endif
#endif
    printf("Fallback constant: %d\n", LAB_FALLBACK);
    lab_finish();
    return EXIT_SUCCESS;
}
