#include "idt.h"
#include "string.h"
#include "stdio.h"
#include "virtual_memory.h"
#include "physic_memory.h"
page_t pgd_kernel[PGD_SIZE] __attribute__((aligned(PAGE_SIZE)));
static pte_t pte_kernel[PTE_COUNT][PTE_SIZE] __attribute__((aligned(PAGE_SIZE)));
void init_virtual_memory() {
    uint32_t kernel_pte_first_idx = PGD_INDEX(PAGE_OFFSET);
    uint32_t i, j;
    for (i = kernel_pte_first_idx, j = 0; i < PTE_COUNT + kernel_pte_first_idx; i++, j++)
        pgd_kernel[i] = ((uint32_t)pte_kernel[j] - PAGE_OFFSET) | PAGE_PRESENT | PAGE_WRITE;
    uint32_t *pte = (uint32_t *)pte_kernel;
    for (i = 1; i < PTE_COUNT * PTE_SIZE; i++)
        pte[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    uint32_t pgd_kernel_phy_addr = (uint32_t)pgd_kernel - PAGE_OFFSET;
    register_interrupt_handler(14, &page_fault);
    switch_pgd(pgd_kernel_phy_addr);
}
void switch_pgd(uint32_t pd) { asm volatile ("mov %0, %%cr3" : : "r" (pd)); }
void map(page_t *pgd_now, uint32_t va, uint32_t pa, uint32_t flags) {   
    uint32_t pgd_idx = PGD_INDEX(va);
    uint32_t pte_idx = PTE_INDEX(va); 
    pte_t *pte = (pte_t *)(pgd_now[pgd_idx] & PAGE_MASK);
    if (!pte) {
        pte = (pte_t *)physic_alloc_page();
        pgd_now[pgd_idx] = (uint32_t)pte | PAGE_PRESENT | PAGE_WRITE;
        pte = (pte_t *)((uint32_t)pte + PAGE_OFFSET);
        bzero(pte, PAGE_SIZE);
    }
	else { pte = (pte_t *)((uint32_t)pte + PAGE_OFFSET); }
    pte[pte_idx] = (pa & PAGE_MASK) | flags;
    asm volatile ("invlpg (%0)" : : "a" (va));
}
void unmap(page_t *pgd_now, uint32_t va) {
    uint32_t pgd_idx = PGD_INDEX(va);
    uint32_t pte_idx = PTE_INDEX(va);
    pte_t *pte = (pte_t *)(pgd_now[pgd_idx] & PAGE_MASK);
    if (!pte)
        return;
    pte = (pte_t *)((uint32_t)pte + PAGE_OFFSET);
    pte[pte_idx] = 0;
    asm volatile ("invlpg (%0)" : : "a" (va));
}
uint32_t get_mapping(page_t *pgd_now, uint32_t va, uint32_t *pa) {
    uint32_t pgd_idx = PGD_INDEX(va);
    uint32_t pte_idx = PTE_INDEX(va);
    pte_t *pte = (pte_t *)(pgd_now[pgd_idx] & PAGE_MASK);
    if (!pte)
        return 0;
    pte = (pte_t *)((uint32_t)pte + PAGE_OFFSET);
    if (pte[pte_idx] != 0 && pa) {
        *pa = pte[pte_idx] & PAGE_MASK;
        return 1;
    }
    return 0;
}
void page_fault(pt_regs *regs) {
    uint32_t cr2;
    asm volatile ("mov %%cr2, %0" : "=r" (cr2));
    printk("Page fault at 0x%x, virtual faulting address 0x%x\n", regs -> eip, cr2);
    printk("Error code: %x\n", regs -> err_code);
    if (!(regs -> err_code & 0x1)) { printk("Because the page wasn't present.\n"); }
    if (regs -> err_code & 0x2) { printk("Write error.\n"); } else { printk("Read error.\n"); }
    if (regs -> err_code & 0x4) { printk("In user mode.\n"); } else { printk("In kernel mode.\n"); }
    if (regs -> err_code & 0x8) { printk("Reserved bits being overwritten.\n"); }
    if (regs -> err_code & 0x10) { printk("The fault occurred during an instruction fetch.\n"); }
    while (1);
}
