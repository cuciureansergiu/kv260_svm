proc dump_mem {startaddr {size_bytes}} {
        mrd -size b -bin -file blob.bin $startaddr $size_bytes
}
