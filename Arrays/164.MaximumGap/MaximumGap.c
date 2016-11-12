/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#if GENERIC_BUCKET_SORT
/*****************************************/
/* Macros                                */
/*****************************************/
#define BUCKET_SZ_FACTOR 16

/*****************************************/
/* Data Structures                       */
/*****************************************/
/*
** Bucket
*/
struct Bucket
{
    int *barr; // bucker contents
    int bsz;   // present size of the bucket
    int blen;  // bucket length
};

/***********************************************************************/
/* AddToBucket: Add an entry and return diff                           */
/*                                                                     */
/***********************************************************************/
int AddToBucket(struct Bucket *bckt, int val)
{
    int *arr = bckt->barr;
    int i = 0, j, mdiff = -1;

    /* Ensure there is space in the bucket */
    if (bckt->bsz == bckt->blen)
        exit(-1);

    /* Insertion sort: Find the location. */
    while (i < bckt->bsz && arr[i] <= val)
        ++i;

    /* Shift the contents to the right */
    j = bckt->bsz;
    while (j > i) {
        arr[j] = arr[j - 1];
        --j;
    }
    arr[j] = val;
    bckt->bsz++;

    /* If it's not the first and only value, then calculate the
    value */
    if (bckt->bsz > 1) {

        /* If it's an intermediate value, then check both the
        possibilities and return the maximum */
        if (j && j < bckt->bsz - 1)
            mdiff = arr[j] - arr[j - 1] > arr[j + 1] - arr[j] ?
                    arr[j] - arr[j - 1] : arr[j + 1] - arr[j];
        /* Else just check the relevant combination */
        else if (j)
            mdiff = arr[j] - arr[j - 1];
        else
            mdiff = arr[j + 1] - arr[j];
    }

    /* Return the difference */
    return mdiff;
}

/***********************************************************************/
/* GetBucketMin: Get the minimum value from the bucket                 */
/*                                                                     */
/***********************************************************************/
int GetBucketMin(struct Bucket *bckt)
{
    /* If the bucket is empty, then return -1 */
    if (!bckt->bsz)
        return -1;
    /* Return the smallest value */
    return bckt->barr[0];
}

/***********************************************************************/
/* GetBucketMax: Get the maximum value from the bucket                 */
/*                                                                     */
/***********************************************************************/
int GetBucketMax(struct Bucket *bckt)
{
    /* If the bucket is empty, then return -1 */
    if (!bckt->bsz)
        return -1;
    /* Return the maximum value */
    return bckt->barr[bckt->bsz - 1];
}

/***********************************************************************/
/* GetMaxBucketDiff: Get the maximum diff from the bucket              */
/*                                                                     */
/***********************************************************************/
int GetBucketMaxDiff(struct Bucket *bckt)
{
    int i, maxdiff = -1;
    int *arr = bckt->barr;

    /* If the bucket is empty, then return -1 */
    if (!bckt->bsz)
        return -1;
    /* Loop and figure out the max diff */
    for (i = bckt->bsz - 1; i > 0; --i)
        if (maxdiff < arr[i] - arr[i - 1])
            maxdiff = arr[i] - arr[i - 1];
    /* Return the max difference */
    return maxdiff;
}

/***********************************************************************/
/* Given an unsorted array, find the maximum difference between the    */
/* successive elements in its sorted form.                             */
/*                                                                     */
/* Try to solve it in linear time/space.                               */
/*                                                                     */
/* Return 0 if the array contains less than 2 elements.                */
/*                                                                     */
/* You may assume all elements in the array are non-negative integers  */
/* and fit in the 32-bit signed integer range.                         */
/***********************************************************************/
int maximumGap(int* nums, int numsSize)
{
    int s = -1, l = -1, i, bcount, bsizes, memorysz, diff, maxdiff = -1;
    int brange, maxbval, minbval;
    struct Bucket *barr;
    int *arr;

    /* Validate the inputs */
    if (!nums || numsSize < 2)
        return 0;

    /* Find the smallest and largest value */
    for (i = 0; i < numsSize; ++i)
    {
        s = (s == -1) || s > nums[i] ? nums[i] : s;
        l = (l == -1) || l < nums[i] ? nums[i] : l;
    }

    /* Calculate the range size of the buckets, the total number of
    buckets and their sizes. */
    bcount = numsSize;
    brange = ((l - s) / bcount) + 1;
    bsizes = (numsSize * BUCKET_SZ_FACTOR) / bcount;


    /* Calculate the total memory size */
    memorysz = (bcount * sizeof(struct Bucket)) +
               (bcount * bsizes * sizeof(int));

    /* Allocate the memory */
    barr = calloc((memorysz / sizeof(int)) + 1, sizeof(int));
    if (!barr)
        return -1;

    /* Initialize the buckets */
    arr = (int *)(barr + bcount);
    for (i = 0; i < bcount; ++i) {
        barr[i].barr = &arr[i * bsizes];
        barr[i].blen = bsizes;
    }

    /* Place all the values into buckets */
    for (i = 0; i < numsSize; ++i)
        AddToBucket(&barr[(nums[i] - s) / brange], nums[i]);

    /* Now get the max difference within the buckets */
    for (i = 0; i < bcount; ++i) {
        diff = GetBucketMaxDiff(&barr[i]);
        if (diff != -1 && diff > maxdiff)
            maxdiff = diff;
    }

    /* Now find all the differences straddling the bucket boundaries */
    i = 0;
    while (i < bcount)
    {
        /* Get the maximum value */
        while (i < bcount - 1 && (maxbval = GetBucketMax(&barr[i])) == -1)
            ++i;
        /* Get the minimum value */
        ++i;
        while (i < bcount && ((minbval = GetBucketMin(&barr[i])) == -1))
            ++i;
        /* If needed, update the maximum difference */
        if (i < bcount && maxdiff < minbval - maxbval)
            maxdiff = minbval - maxbval;
    }

    /* Live free */
    free(barr);

    /* Return the maximum difference */
    return maxdiff;
}
#else /* Radix Sort */
/*************************************************/
/* Configuration Macros                          */
/*************************************************/
#define RADIX_BIT_COUNT 8
#define RADIX_MASK     ((1 << RADIX_BIT_COUNT) - 1)

/***********************************************************************/
/* RadixSort: Run a radix sort                                         */
/* URL: https://www.cs.usfca.edu/~galles/visualization/RadixSort.html  */
/*                                                                     */
/***********************************************************************/
void RadixSort(int *a, int len)
{
    int rcount[RADIX_MASK + 1] = {0};
    int i, roff, small, large, shift = 0;
    int *arr = a, *arr2, *ta;

    /* Allocate the sort array */
    if ((ta = arr2 = malloc(sizeof(int) * len)) == NULL)
        return;

    /* Find the smallest and largest element */
    small = large = a[0];
    for (i = 1; i < len; ++i) {
        small = small > a[i] ? a[i] : small;
        large = large < a[i] ? a[i] : large;
    }

    /* Loop until we are not done! */
    while (shift < (sizeof(int) * 8) && ((large - small) >> shift) != 0)
    {
        /* Generate the number of entries for each bucket, then accumulate
        their counts */
        for (i = 0; i < len; ++i)
            rcount[((arr[i] - small) >> shift) & RADIX_MASK]++;
        for (i = 1; i < RADIX_MASK + 1; ++i)
            rcount[i] += rcount[i - 1];

        /* Move the contents creating buckets sorted based on the
           corresponding LSBs. Note that we are traversing from the back
           of the array, this means the larger entries go to larger
           offsets within the buckets. */
        for (i = len - 1; i >= 0; --i){
            /* Calculate the bucket for the value. */
            roff = ((arr[i] - small) >> shift) & RADIX_MASK;
            arr2[rcount[roff] - 1] = arr[i];
            rcount[roff]--; // decrement the bucket offset
        }

        /* Swap the arrays & Reset counters. */
        arr2 = (arr2 == a) ? ta : a;
        arr = (arr == a) ? ta : a;
        memset(rcount, 0, sizeof(int) * (RADIX_MASK + 1));
        shift += RADIX_BIT_COUNT;
    }

    /* If needed, make a copy of the array */
    if (arr != a) {
        memcpy(a, arr, sizeof(int) * len);
        arr2 = arr;
    }
    /* Live free */
    free(arr2);
}

/***********************************************************************/
/* Given an unsorted array, find the maximum difference between the    */
/* successive elements in its sorted form.                             */
/*                                                                     */
/* Try to solve it in linear time/space.                               */
/*                                                                     */
/* Return 0 if the array contains less than 2 elements.                */
/*                                                                     */
/* You may assume all elements in the array are non-negative integers  */
/* and fit in the 32-bit signed integer range.                         */
/***********************************************************************/
int maximumGap(int* nums, int numsSize)
{
    int i, maxdiff;

    /* Need not work with arrays less than 2 elements */
    if (!nums || numsSize < 2)
        return 0;

    /* Do a radix sort */
    RadixSort(nums, numsSize);

    /* Find the maxdiff */
    for (i = 1; i < numsSize; ++i)
        if ((i == 1) || nums[i] - nums[i - 1] > maxdiff)
            maxdiff = nums[i] - nums[i - 1];
    return maxdiff;
}
#endif

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2,3,4,5,6,1,2,344,123,677};
    //int a[] = {12115,10639,2351,29639,31300,11245,16323,24899,8043,4076,17583,15872,19443,12887,5286,6836,31052,25648,17584,24599,13787,24727,12414,5098,26096,23020,25338,28472,4345,25144,27939,10716,3830,13001,7960,8003,10797,5917,22386,12403,2335,32514,23767,1868,29882,31738,30157,7950,20176,11748,13003,13852,19656,25305,7830,3328,19092,28245,18635,5806,18915,31639,24247,32269,29079,24394,18031,9395,8569,11364,28701,32496,28203,4175,20889,28943,6495,14919,16441,4568,23111,20995,7401,30298,2636,16791,1662,27367,2563,22169,1607,15711,29277,32386,27365,31922,26142,8792};
    //int a[] = {601408776,63967816,431363697,242509930,15970592,60284088,228037800,147629558,220782926,55455864,456541040,106650540,17290078,52153098,103139530,294196042,16568100,426864152,61916064,657788565,166159446,1741650,101791800,28206276,6223796,524849590,125389882,84399672,153834912,164568204,1866165,283209696,560993994,16266096,219635658,9188983,485969304,782013650,120332636,44659356,444517408,36369045,47370708,18542592,98802990,137690000,124889895,56062800,265421676,309417680,4634176,801661539,510541206,258227892,398938089,47255754,152260962,409663140,102847688,45756553,377936600,269498,375738702,263761134,53797945,329493948,224442208,508336845,189507850,40944620,127879560,119629476,186894520,62409156,693721503,4289916,523899936,28955240,266488028,20356650,40769391,483694272,97988044,84102,67246047,310688630,41288643,58965588,42881432,152159462,94786355,174917835,119224652,525034376,261516,274800528,62643819,23613832,8397240,797832131,855155367,337066320,26341480,61932200,20661075,515542796,390337500,522552030,43538516,150800550,116747540,152989123,488640056,700610304,233604,344277340,21439176,9397864,16365822,73027584,453041413,197374275,157735188,15273822,187081152,379611084,865005504,223099767,80478651,377729400,186738219,34738263,16634072,112791343,99631856,119364960,477106486,583953920,624509809,188442472,294181256,213023715,146645884,149530380,497592753,132170327,72770643,126683010,405141255,590214306,26670714,95582385,162080790,231120099,8946432,204967980,592849110,54120698,375915096,602145859,5346440,226337825,425156369,653591624,578483360,572410800,32290700,381384563,149939976,183225375,155695620,38307636,457513760,97085778,75200576,8068176,221650296,556889418,252495726,895020231,19932465,156334887,191383314,348432526,368701264,14315598,148936587,279419435,237325542,252587218,322929504,26331343,355297676,600420786,652017765,51673622,159015675};
    int len = sizeof(a) / sizeof(int);
    printf("Maximum Gap = %d :\n", maximumGap(a, len));
    return 0;
}
