#ifndef _ACPI_H
#define _ACPI_H

#include "../../../../limine/limine.h"

#include "../../lib/string.h"
#include "../../util/util.h"

static uint64_t* rsdp_address = NULL;
static uint8_t rsdp_revision = 0;

struct RSDP_t
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
} __attribute__ ((packed));

struct XSDP_t
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;   //deprecated in version 2.0+

    uint32_t Length;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
} __attribute__ ((packed));


static struct RSDP_t* rsdp_t = NULL;
static struct XSDP_t* xsdp_t = NULL;

void init_RSDP();
void shutdown();
void restart();

#endif