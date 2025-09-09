#include "acpi.h"

#include "../../bootloader/limine_requests.h"
#include "../../util/util.h"

void init_RSDP()
{
    if (rsdp_request.response == NULL)
    {
        hcf();
    }
    else
    {
        rsdp_revision = rsdp_request.response->revision;
        if (rsdp_revision == 0)
        {
            rsdp_t = (struct RSDP_t*)&rsdp_request.response->address;
            xsdp_t = NULL;
        }
        else if (rsdp_revision >= 2)
        {
            rsdp_t = NULL;
            xsdp_t = (struct XSDP_t*)&rsdp_request.response->address;
        }
    }

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


void shutdown()
{

}

void restart()
{

}