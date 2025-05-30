/* $OpenBSD: sha256_amd64.c,v 1.2 2024/11/16 15:31:36 jsing Exp $ */
/*
 * Copyright (c) 2024 Joel Sing <jsing@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <openssl/sha.h>

#include "crypto_arch.h"

void sha256_block_generic(SHA256_CTX *ctx, const void *in, size_t num);
void sha256_block_shani(SHA256_CTX *ctx, const void *in, size_t num);

void
sha256_block_data_order(SHA256_CTX *ctx, const void *in, size_t num)
{
	if ((crypto_cpu_caps_amd64 & CRYPTO_CPU_CAPS_AMD64_SHA) != 0) {
		sha256_block_shani(ctx, in, num);
		return;
	}

	sha256_block_generic(ctx, in, num);
}
