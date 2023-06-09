/*! Interrupt handling - 'arch' layer (only basic operations) */

#define _ARCH_INTERRUPTS_C_
#include "interrupt.h"

#include <arch/processor.h>
#include <kernel/errno.h>
#include <lib/string.h>

/*! Interrupt controller device */
extern arch_ic_t IC_DEV;
static arch_ic_t *icdev = &IC_DEV;

/*! interrupt handlers */
static void (*ihandler[INTERRUPTS])(unsigned int);

/*! Initialize interrupt susubsystem (in 'arch' layer) */
void arch_init_interrupts()
{
	icdev->init();

	memset(ihandler, 0, sizeof(ihandler));
}

/*!
 * enable and disable interrupts generated outside processor, controller by
 * interrupt controller (PIC or APIC or ...)
 */
void arch_irq_enable(unsigned int irq)
{
	icdev->enable_irq(irq);
}
void arch_irq_disable(unsigned int irq)
{
	icdev->disable_irq(irq);
}

/*! Register handler function for particular interrupt number */
void *arch_register_interrupt_handler(unsigned int irq_num, void *handler)
{
	void *old_handler = NULL;

	if (irq_num < INTERRUPTS)
	{
		old_handler = ihandler[irq_num];
		ihandler[irq_num] = handler;
	}
	else {
		LOG(ERROR, "Interrupt %d can't be used!\n", irq_num);
		halt();
	}

	return old_handler;
}

/*! Unregister handler function for particular interrupt number */
void *arch_unregister_interrupt_handler(unsigned int irq_num)
{
	void *old_handler = NULL;
	ASSERT(irq_num >= 0 && irq_num < INTERRUPTS);

	old_handler = ihandler[irq_num];
	ihandler[irq_num] = NULL;

	return old_handler;
}

/*!
 * "Forward" interrupt handling to registered handler
 * (called from interrupts.S)
 */
void arch_interrupt_handler(int irq_num)
{
	if (irq_num < INTERRUPTS && ihandler[irq_num])
	{
		/* Call registered handler */
		ihandler[irq_num](irq_num);

		if (icdev->at_exit)
			icdev->at_exit(irq_num);
	}

	else if (irq_num < INTERRUPTS)
	{
		LOG(ERROR, "Unregistered interrupt: %d - %s!\n",
		      irq_num, icdev->int_descr(irq_num));
		halt();
	}
	else {
		LOG(ERROR, "Unregistered interrupt: %d !\n", irq_num);
		halt();
	}
}
