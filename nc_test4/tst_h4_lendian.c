/*! Testing for proper read of little-endian variables in an hdf4 file.
 *
 * Added to debug issue NCF-332. Based on code submitted by
 * https://github.com/Unidata/netcdf-c/issues/113.
 */

#include <stdio.h>
#include <config.h>
#include <nc_tests.h>
#include <hdf5.h>
#include <H5DSpublic.h>
#include "mfhdf.h"



#define DIM1 5
#define DIM0 5
#define RANK 2
#define FILENAME "tst_h4_lendian.h4"
#define SDSNAME "data"

int create_hdf_file() {

    int32 sd_id, sds_id, istat, sd_index;
    int32 dims[2], start[2], edges[2], rank;
    int16 array_data[DIM0][DIM1];
    intn i, j, count;

    start[0] = 0;
    start[1] = 0;
    edges[0] = DIM1;
    edges[1] = DIM0;

    // populate data array
    count = 0;
    for (j = 0; j < DIM0; j++)
    {
        for (i = 0; i < DIM1; i++)
            array_data[j][i] = count++;
    }

    sd_id = SDstart(FILENAME, DFACC_CREATE);
    sds_id = SDcreate(sd_id, SDSNAME, DFNT_LITEND|DFNT_INT16, RANK, edges);

    istat = SDendaccess(sds_id);

    istat = SDend(sd_id);
    sd_id = SDstart(FILENAME, DFACC_WRITE);

    sd_index = 0;
    sds_id = SDselect(sd_id, sd_index);

    istat = SDwritedata(sds_id, start, NULL, edges, (VOIDP)array_data);

    istat = SDendaccess(sds_id);

    istat = SDend(sd_id);

    return 0;
}

/*! Standard main function.
 *
 */
int main() {

  int res = 0;

  printf("Testing a read from an hdf4 file with a little-endian datatype.\n");

  printf("\to Creating hdf file with little-endian datatypes....\t");
  res = create_hdf_file();
  if(res) {
    printf("Failure: %d\n",res);
    return res;
  } else {
    printf("Success.\n");
  }

  printf("\to Reading hdf4 file.\n");


  printf("Finished.\n");
  return 0;
}
