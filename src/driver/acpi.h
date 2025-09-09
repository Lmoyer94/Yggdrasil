#ifndef _ACPI_H
#define _ACPI_H

#include "../../../limine/limine.h"

#include "../lib/string.h"
#include "../util/util.h"

uint64_t* rsdp_address;
uint8_t rsdp_revision;

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


struct RSDP_t* rsdp_t;
struct XSDP_t* xsdp_t;

void init_RSDP()
{
    if (rsdp_revision == 0)
    {   
        if (memcmp(rsdp_t->Signature, "RSD PTR ", 8))
        {
            uint64_t check = 0;
            uint8_t* ptr = (uint8_t*) rsdp_t;
            for (uint8_t i = 0; i < 20; i++)
                check += ptr[i];

            if ((uint8_t)check == 0)
            {
                //do nothing
            }
            else
            {
                kpanic("ACPI 1.0 is not checksum validated!");
            }
        }
        else 
        {
            kpanic("ACPI 1.0 is not signature validated!");
        }
    }
    else if (rsdp_revision >= 2)
    {
        uint64_t check1 = 0;
        uint64_t check2 = 0;
        for (int i = 0; i < 8; i++)
        {
            check1 += xsdp_t->Signature[i];
        }
        check1 += xsdp_t->Checksum;
        for (int i = 0; i < 6; i++)
        {
            check1 += xsdp_t->OEMID[i];
        }
        check1 += xsdp_t->Revision;
        check1 += xsdp_t->RsdtAddress;
        if ((check1 % 0x100) != 0)
        {
            kpanic("RSDP 2.0+ RSDP checksum failed!");
        }

        check2 = check1;
        check2 += xsdp_t->Length;
        check2 += xsdp_t->XsdtAddress;
        check2 += xsdp_t->ExtendedChecksum;
        for (int i = 0; i < 3; i++)
        {
            check2 += xsdp_t->reserved[i];
        }

        if ((check2 % 0x100) != 0)
        {
            kpanic("RSDP 2.0+ XSDP checksum failed!");
        }
    }
}

#endif