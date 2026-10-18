#include "qemu/osdep.h"
#include "hw/core/boards.h"
#include "qom/object.h"
#include "system/address-spaces.h"
#include "hw/core/cpu.h"
#include "target/arm/cpu.h"
#include "target/arm/cpu-qom.h"
#include "qemu/units.h"

#define TYPE_HTC_DREAM_MACHINE MACHINE_TYPE_NAME("htc-dream")
OBJECT_DECLARE_SIMPLE_TYPE(HTCDreamMachineState, HTC_DREAM_MACHINE)

struct HTCDreamMachineState {
	MachineState parent;
};

static void htc_dream_machine_init(MachineState *machine) {
	CPUState *cpu = cpu_create(machine->cpu_type);
	memory_region_add_subregion(get_system_memory(), 0x10000000, machine->ram);
	cpu_set_pc(cpu, 0x10000000);
}

static void htc_dream_machine_class_init(ObjectClass *oc, const void *data) {
	MachineClass *mc = MACHINE_CLASS(oc);
	mc->desc = "HTC Dream smartphone (from QEMU-Multidroid)";
	mc->default_cpu_type = ARM_CPU_TYPE_NAME("arm1136");
	mc->default_ram_size = 192 * MiB;
	mc->default_ram_id = "htc-dream.ram";
	mc->init = htc_dream_machine_init;
}

static const TypeInfo htc_dream_machine_type = {
	.name = TYPE_HTC_DREAM_MACHINE,
	.parent = TYPE_MACHINE,
	.instance_size = sizeof(HTCDreamMachineState),
	.class_init = htc_dream_machine_class_init,
};

static void htc_dream_machine_register_types(void) {
	type_register_static(&htc_dream_machine_type);
}

type_init(htc_dream_machine_register_types);