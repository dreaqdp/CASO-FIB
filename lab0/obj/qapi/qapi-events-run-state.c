/* AUTOMATICALLY GENERATED, DO NOT MODIFY */

/*
 * Schema-defined QAPI/QMP events
 *
 * Copyright (c) 2014 Wenchao Xia
 * Copyright (c) 2015-2018 Red Hat Inc.
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "qapi-events.h"
#include "qapi-visit-run-state.h"
#include "qapi/error.h"
#include "qapi/qmp/qdict.h"
#include "qapi/qobject-output-visitor.h"
#include "qapi/qmp-event.h"


void qapi_event_send_shutdown(bool guest)
{
    QDict *qmp;
    QMPEventFuncEmit emit;
    QObject *obj;
    Visitor *v;
    q_obj_SHUTDOWN_arg param = {
        guest
    };

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("SHUTDOWN");

    v = qobject_output_visitor_new(&obj);

    visit_start_struct(v, "SHUTDOWN", NULL, 0, &error_abort);
    visit_type_q_obj_SHUTDOWN_arg_members(v, &param, &error_abort);
    visit_check_struct(v, &error_abort);
    visit_end_struct(v, NULL);

    visit_complete(v, &obj);
    qdict_put_obj(qmp, "data", obj);
    emit(QAPI_EVENT_SHUTDOWN, qmp);

    visit_free(v);
    qobject_unref(qmp);
}

void qapi_event_send_powerdown(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("POWERDOWN");

    emit(QAPI_EVENT_POWERDOWN, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_reset(bool guest)
{
    QDict *qmp;
    QMPEventFuncEmit emit;
    QObject *obj;
    Visitor *v;
    q_obj_RESET_arg param = {
        guest
    };

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("RESET");

    v = qobject_output_visitor_new(&obj);

    visit_start_struct(v, "RESET", NULL, 0, &error_abort);
    visit_type_q_obj_RESET_arg_members(v, &param, &error_abort);
    visit_check_struct(v, &error_abort);
    visit_end_struct(v, NULL);

    visit_complete(v, &obj);
    qdict_put_obj(qmp, "data", obj);
    emit(QAPI_EVENT_RESET, qmp);

    visit_free(v);
    qobject_unref(qmp);
}

void qapi_event_send_stop(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("STOP");

    emit(QAPI_EVENT_STOP, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_resume(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("RESUME");

    emit(QAPI_EVENT_RESUME, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_suspend(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("SUSPEND");

    emit(QAPI_EVENT_SUSPEND, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_suspend_disk(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("SUSPEND_DISK");

    emit(QAPI_EVENT_SUSPEND_DISK, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_wakeup(void)
{
    QDict *qmp;
    QMPEventFuncEmit emit;

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("WAKEUP");

    emit(QAPI_EVENT_WAKEUP, qmp);

    qobject_unref(qmp);
}

void qapi_event_send_watchdog(WatchdogAction action)
{
    QDict *qmp;
    QMPEventFuncEmit emit;
    QObject *obj;
    Visitor *v;
    q_obj_WATCHDOG_arg param = {
        action
    };

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("WATCHDOG");

    v = qobject_output_visitor_new(&obj);

    visit_start_struct(v, "WATCHDOG", NULL, 0, &error_abort);
    visit_type_q_obj_WATCHDOG_arg_members(v, &param, &error_abort);
    visit_check_struct(v, &error_abort);
    visit_end_struct(v, NULL);

    visit_complete(v, &obj);
    qdict_put_obj(qmp, "data", obj);
    emit(QAPI_EVENT_WATCHDOG, qmp);

    visit_free(v);
    qobject_unref(qmp);
}

void qapi_event_send_guest_panicked(GuestPanicAction action, bool has_info, GuestPanicInformation *info)
{
    QDict *qmp;
    QMPEventFuncEmit emit;
    QObject *obj;
    Visitor *v;
    q_obj_GUEST_PANICKED_arg param = {
        action, has_info, info
    };

    emit = qmp_event_get_func_emit();
    if (!emit) {
        return;
    }

    qmp = qmp_event_build_dict("GUEST_PANICKED");

    v = qobject_output_visitor_new(&obj);

    visit_start_struct(v, "GUEST_PANICKED", NULL, 0, &error_abort);
    visit_type_q_obj_GUEST_PANICKED_arg_members(v, &param, &error_abort);
    visit_check_struct(v, &error_abort);
    visit_end_struct(v, NULL);

    visit_complete(v, &obj);
    qdict_put_obj(qmp, "data", obj);
    emit(QAPI_EVENT_GUEST_PANICKED, qmp);

    visit_free(v);
    qobject_unref(qmp);
}

/* Dummy declaration to prevent empty .o file */
char dummy_qapi_events_run_state_c;
