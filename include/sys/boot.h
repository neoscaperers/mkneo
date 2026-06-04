//
//  boot.h
//  
//
//  Created by neo on 6/4/26.
//

#ifndef _SYS_BOOT_H
#define _SYS_BOOT_H

#include <sys/types.h>

struct boot_s {
    phys_t memory_start;
    phys_t memory_end;
};

#endif /*_SYS_BOOT_H*/
