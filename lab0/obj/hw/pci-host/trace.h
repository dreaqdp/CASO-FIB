/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_HW_PCI_HOST_GENERATED_TRACERS_H
#define TRACE_HW_PCI_HOST_GENERATED_TRACERS_H

#include "qemu-common.h"
#include "trace/control.h"

extern TraceEvent _TRACE_GRACKLE_SET_IRQ_EVENT;
extern TraceEvent _TRACE_SABRE_SET_REQUEST_EVENT;
extern TraceEvent _TRACE_SABRE_CLEAR_REQUEST_EVENT;
extern TraceEvent _TRACE_SABRE_CONFIG_WRITE_EVENT;
extern TraceEvent _TRACE_SABRE_CONFIG_READ_EVENT;
extern TraceEvent _TRACE_SABRE_PCI_CONFIG_WRITE_EVENT;
extern TraceEvent _TRACE_SABRE_PCI_CONFIG_READ_EVENT;
extern TraceEvent _TRACE_SABRE_PCI_SET_IRQ_EVENT;
extern TraceEvent _TRACE_SABRE_PCI_SET_OBIO_IRQ_EVENT;
extern TraceEvent _TRACE_UNIN_SET_IRQ_EVENT;
extern TraceEvent _TRACE_UNIN_GET_CONFIG_REG_EVENT;
extern TraceEvent _TRACE_UNIN_DATA_WRITE_EVENT;
extern TraceEvent _TRACE_UNIN_DATA_READ_EVENT;
extern TraceEvent _TRACE_UNIN_WRITE_EVENT;
extern TraceEvent _TRACE_UNIN_READ_EVENT;
extern uint16_t _TRACE_GRACKLE_SET_IRQ_DSTATE;
extern uint16_t _TRACE_SABRE_SET_REQUEST_DSTATE;
extern uint16_t _TRACE_SABRE_CLEAR_REQUEST_DSTATE;
extern uint16_t _TRACE_SABRE_CONFIG_WRITE_DSTATE;
extern uint16_t _TRACE_SABRE_CONFIG_READ_DSTATE;
extern uint16_t _TRACE_SABRE_PCI_CONFIG_WRITE_DSTATE;
extern uint16_t _TRACE_SABRE_PCI_CONFIG_READ_DSTATE;
extern uint16_t _TRACE_SABRE_PCI_SET_IRQ_DSTATE;
extern uint16_t _TRACE_SABRE_PCI_SET_OBIO_IRQ_DSTATE;
extern uint16_t _TRACE_UNIN_SET_IRQ_DSTATE;
extern uint16_t _TRACE_UNIN_GET_CONFIG_REG_DSTATE;
extern uint16_t _TRACE_UNIN_DATA_WRITE_DSTATE;
extern uint16_t _TRACE_UNIN_DATA_READ_DSTATE;
extern uint16_t _TRACE_UNIN_WRITE_DSTATE;
extern uint16_t _TRACE_UNIN_READ_DSTATE;
#define TRACE_GRACKLE_SET_IRQ_ENABLED 1
#define TRACE_SABRE_SET_REQUEST_ENABLED 1
#define TRACE_SABRE_CLEAR_REQUEST_ENABLED 1
#define TRACE_SABRE_CONFIG_WRITE_ENABLED 1
#define TRACE_SABRE_CONFIG_READ_ENABLED 1
#define TRACE_SABRE_PCI_CONFIG_WRITE_ENABLED 1
#define TRACE_SABRE_PCI_CONFIG_READ_ENABLED 1
#define TRACE_SABRE_PCI_SET_IRQ_ENABLED 1
#define TRACE_SABRE_PCI_SET_OBIO_IRQ_ENABLED 1
#define TRACE_UNIN_SET_IRQ_ENABLED 1
#define TRACE_UNIN_GET_CONFIG_REG_ENABLED 1
#define TRACE_UNIN_DATA_WRITE_ENABLED 1
#define TRACE_UNIN_DATA_READ_ENABLED 1
#define TRACE_UNIN_WRITE_ENABLED 1
#define TRACE_UNIN_READ_ENABLED 1
#include "qemu/log-for-trace.h"


#define TRACE_GRACKLE_SET_IRQ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_GRACKLE_SET_IRQ) || \
    false)

static inline void _nocheck__trace_grackle_set_irq(int irq_num, int level)
{
    if (trace_event_get_state(TRACE_GRACKLE_SET_IRQ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:grackle_set_irq " "set_irq num %d level %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num, level);
    }
}

static inline void trace_grackle_set_irq(int irq_num, int level)
{
    if (true) {
        _nocheck__trace_grackle_set_irq(irq_num, level);
    }
}

#define TRACE_SABRE_SET_REQUEST_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_SET_REQUEST) || \
    false)

static inline void _nocheck__trace_sabre_set_request(int irq_num)
{
    if (trace_event_get_state(TRACE_SABRE_SET_REQUEST) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_set_request " "request irq %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num);
    }
}

static inline void trace_sabre_set_request(int irq_num)
{
    if (true) {
        _nocheck__trace_sabre_set_request(irq_num);
    }
}

#define TRACE_SABRE_CLEAR_REQUEST_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_CLEAR_REQUEST) || \
    false)

static inline void _nocheck__trace_sabre_clear_request(int irq_num)
{
    if (trace_event_get_state(TRACE_SABRE_CLEAR_REQUEST) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_clear_request " "clear request irq %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num);
    }
}

static inline void trace_sabre_clear_request(int irq_num)
{
    if (true) {
        _nocheck__trace_sabre_clear_request(irq_num);
    }
}

#define TRACE_SABRE_CONFIG_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_CONFIG_WRITE) || \
    false)

static inline void _nocheck__trace_sabre_config_write(uint64_t addr, uint64_t val)
{
    if (trace_event_get_state(TRACE_SABRE_CONFIG_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_config_write " "addr 0x%"PRIx64" val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, val);
    }
}

static inline void trace_sabre_config_write(uint64_t addr, uint64_t val)
{
    if (true) {
        _nocheck__trace_sabre_config_write(addr, val);
    }
}

#define TRACE_SABRE_CONFIG_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_CONFIG_READ) || \
    false)

static inline void _nocheck__trace_sabre_config_read(uint64_t addr, uint64_t val)
{
    if (trace_event_get_state(TRACE_SABRE_CONFIG_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_config_read " "addr 0x%"PRIx64" val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, val);
    }
}

static inline void trace_sabre_config_read(uint64_t addr, uint64_t val)
{
    if (true) {
        _nocheck__trace_sabre_config_read(addr, val);
    }
}

#define TRACE_SABRE_PCI_CONFIG_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_PCI_CONFIG_WRITE) || \
    false)

static inline void _nocheck__trace_sabre_pci_config_write(uint64_t addr, uint64_t val)
{
    if (trace_event_get_state(TRACE_SABRE_PCI_CONFIG_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_pci_config_write " "addr 0x%"PRIx64" val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, val);
    }
}

static inline void trace_sabre_pci_config_write(uint64_t addr, uint64_t val)
{
    if (true) {
        _nocheck__trace_sabre_pci_config_write(addr, val);
    }
}

#define TRACE_SABRE_PCI_CONFIG_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_PCI_CONFIG_READ) || \
    false)

static inline void _nocheck__trace_sabre_pci_config_read(uint64_t addr, uint64_t val)
{
    if (trace_event_get_state(TRACE_SABRE_PCI_CONFIG_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_pci_config_read " "addr 0x%"PRIx64" val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, val);
    }
}

static inline void trace_sabre_pci_config_read(uint64_t addr, uint64_t val)
{
    if (true) {
        _nocheck__trace_sabre_pci_config_read(addr, val);
    }
}

#define TRACE_SABRE_PCI_SET_IRQ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_PCI_SET_IRQ) || \
    false)

static inline void _nocheck__trace_sabre_pci_set_irq(int irq_num, int level)
{
    if (trace_event_get_state(TRACE_SABRE_PCI_SET_IRQ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_pci_set_irq " "set irq_in %d level %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num, level);
    }
}

static inline void trace_sabre_pci_set_irq(int irq_num, int level)
{
    if (true) {
        _nocheck__trace_sabre_pci_set_irq(irq_num, level);
    }
}

#define TRACE_SABRE_PCI_SET_OBIO_IRQ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_SABRE_PCI_SET_OBIO_IRQ) || \
    false)

static inline void _nocheck__trace_sabre_pci_set_obio_irq(int irq_num, int level)
{
    if (trace_event_get_state(TRACE_SABRE_PCI_SET_OBIO_IRQ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:sabre_pci_set_obio_irq " "set irq %d level %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num, level);
    }
}

static inline void trace_sabre_pci_set_obio_irq(int irq_num, int level)
{
    if (true) {
        _nocheck__trace_sabre_pci_set_obio_irq(irq_num, level);
    }
}

#define TRACE_UNIN_SET_IRQ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_SET_IRQ) || \
    false)

static inline void _nocheck__trace_unin_set_irq(int irq_num, int level)
{
    if (trace_event_get_state(TRACE_UNIN_SET_IRQ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_set_irq " "setting INT %d = %d" "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , irq_num, level);
    }
}

static inline void trace_unin_set_irq(int irq_num, int level)
{
    if (true) {
        _nocheck__trace_unin_set_irq(irq_num, level);
    }
}

#define TRACE_UNIN_GET_CONFIG_REG_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_GET_CONFIG_REG) || \
    false)

static inline void _nocheck__trace_unin_get_config_reg(uint32_t reg, uint32_t addr, uint32_t retval)
{
    if (trace_event_get_state(TRACE_UNIN_GET_CONFIG_REG) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_get_config_reg " "converted config space accessor 0x%"PRIx32 "/0x%"PRIx32 " -> 0x%"PRIx32 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , reg, addr, retval);
    }
}

static inline void trace_unin_get_config_reg(uint32_t reg, uint32_t addr, uint32_t retval)
{
    if (true) {
        _nocheck__trace_unin_get_config_reg(reg, addr, retval);
    }
}

#define TRACE_UNIN_DATA_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_DATA_WRITE) || \
    false)

static inline void _nocheck__trace_unin_data_write(uint64_t addr, unsigned len, uint64_t val)
{
    if (trace_event_get_state(TRACE_UNIN_DATA_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_data_write " "write addr 0x%"PRIx64 " len %d val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, len, val);
    }
}

static inline void trace_unin_data_write(uint64_t addr, unsigned len, uint64_t val)
{
    if (true) {
        _nocheck__trace_unin_data_write(addr, len, val);
    }
}

#define TRACE_UNIN_DATA_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_DATA_READ) || \
    false)

static inline void _nocheck__trace_unin_data_read(uint64_t addr, unsigned len, uint64_t val)
{
    if (trace_event_get_state(TRACE_UNIN_DATA_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_data_read " "read addr 0x%"PRIx64 " len %d val 0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, len, val);
    }
}

static inline void trace_unin_data_read(uint64_t addr, unsigned len, uint64_t val)
{
    if (true) {
        _nocheck__trace_unin_data_read(addr, len, val);
    }
}

#define TRACE_UNIN_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_WRITE) || \
    false)

static inline void _nocheck__trace_unin_write(uint64_t addr, uint64_t value)
{
    if (trace_event_get_state(TRACE_UNIN_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_write " "addr=0x%" PRIx64 " val=0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, value);
    }
}

static inline void trace_unin_write(uint64_t addr, uint64_t value)
{
    if (true) {
        _nocheck__trace_unin_write(addr, value);
    }
}

#define TRACE_UNIN_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_UNIN_READ) || \
    false)

static inline void _nocheck__trace_unin_read(uint64_t addr, uint64_t value)
{
    if (trace_event_get_state(TRACE_UNIN_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log("%d@%zu.%06zu:unin_read " "addr=0x%" PRIx64 " val=0x%"PRIx64 "\n",
                 getpid(),
                 (size_t)_now.tv_sec, (size_t)_now.tv_usec
                 , addr, value);
    }
}

static inline void trace_unin_read(uint64_t addr, uint64_t value)
{
    if (true) {
        _nocheck__trace_unin_read(addr, value);
    }
}
#endif /* TRACE_HW_PCI_HOST_GENERATED_TRACERS_H */
