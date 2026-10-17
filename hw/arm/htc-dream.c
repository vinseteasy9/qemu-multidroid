#include "qemu/osdep.h"
#include "hw/core/boards.h"
#include "hw/arm/boot.h"
#include "qom/object.h"
#include "qemu/units.h"
#include "qapi/error.h"
#include "system/address-spaces.h"

struct HTCDreamMachineState {
	MachineState parent;
	ARMCPU *cpu;
	MemoryRegion ram;
};

#define TYPE_HTC_DREAM_MACHINE MACHINE_TYPE_NAME("htc-dream")
OBJECT_DECLARE_SIMPLE_TYPE(HTCDreamMachineState, HTC_DREAM_MACHINE)

static void htc_dream_init(MachineState *machine) {
	HTCDreamMachineState *s = HTC_DREAM_MACHINE(machine);
	MemoryRegion *sysmem = get_system_memory();
	Object *cpuobj;
	Error *err = NULL;
	memory_region_init_ram(&s->ram, OBJECT(machine), "htc-dream.ram", machine->ram_size, &err);
	if (err) exit(1);
	memory_region_add_subregion(sysmem, 0x10000000, &s->ram);
	s->cpu = ARM_CPU(object_new(ARM_CPU_TYPE_NAME("arm1136")));
	object_property_add_child(OBJECT(machine), "cpu", OBJECT(s->cpu));
}

static void htc_dream_machine_class_init(ObjectClass *oc, const void *data) {
	MachineClass *mc = MACHINE_CLASS(oc);
	mc->desc = "HTC Dream smartphone (from QEMU-MultiDroid)";
	mc->init = htc_dream_init;
	mc->default_cpu_type = ARM_CPU_TYPE_NAME("arm1136");
	mc->default_ram_size = 192 * MiB;
}

static const TypeInfo htc_dream_machine_types[] = {
	{
		.name = TYPE_HTC_DREAM_MACHINE,
		.parent = TYPE_MACHINE,
		.instance_size = sizeof(HTCDreamMachineState),
		.class_init = htc_dream_machine_class_init,
	}
};

DEFINE_TYPES(htc_dream_machine_types);