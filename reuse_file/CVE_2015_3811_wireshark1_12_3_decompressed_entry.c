

static guint8 *decompressed_entry( guint8 *src, guint8 *dst, int *len, guint8 * buf_start, guint8 *buf_end){

/* do the decompression for one field */

	guint16 data_offset, data_cnt;
	guint8 tmp = *src;

	data_offset = (*(src++) & 0xf) << 8;	/* get high byte */
	data_offset += *(src++);		/* add next byte */

	if (( tmp & 0xf0) == 0x10){		/* 2 byte count */
		data_cnt = *src;
		data_cnt++;

	}else {					/* one byte count */
		data_cnt = tmp >> 4;
		data_cnt++;
	}


	src = (dst - 1 - data_offset);
	if ( src < buf_start)
		src += MAX_WIN_BUF_LEN;


/*XXX could do some fancy memory moves, later if speed is problem */

	while( data_cnt--){
		*dst = *src;
		if ( ++(*len) >MAX_WCP_BUF_LEN){
			return NULL;	/* end of buffer error */
		}
		if ( dst++ == buf_end)
			dst = buf_start;
		if ( src++ == buf_end)
			src = buf_start;

	}
	return dst;
}