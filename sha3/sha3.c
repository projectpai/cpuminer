/*
 * Copyright (c) 2020 The Project PAI Foundation
 * Distributed under the MIT software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include "cpuminer-config.h"
#include "sha3/tiny_sha3.h"
#include "miner.h"

/*
 * Search for hashes that meet the target requirements.
 */
int scanhash_shake256(int thr_id, uint32_t *pdata, const uint32_t *ptarget, uint32_t max_nonce, unsigned long *hashes_done)
{
    uint32_t hash[8] __attribute__((aligned(32)));
    uint32_t n = pdata[19] - 1;
    const uint32_t first_nonce = pdata[19];

    sha3_ctx_t ctx;
    do {
        pdata[19] = ++n;

        shake256_init(&ctx);
        shake_update(&ctx, (uint8_t*)pdata, hyc_data_size);
        shake_xof(&ctx);
        for (int i = 0; i < 512; i += 32)
            shake_out(&ctx, (uint8_t*)hash, 32);

        if (fulltest(hash, ptarget)) {
            *hashes_done = n - first_nonce + 1;
            return 1;
        }
    } while (n < max_nonce && !work_restart[thr_id].restart);

    *hashes_done = n - first_nonce + 1;
    pdata[19] = n;

    return 0;
}
