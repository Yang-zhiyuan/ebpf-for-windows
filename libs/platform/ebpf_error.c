// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT

#if !defined(_AMD64_)
#define _AMD64_
#endif
#include <ntdef.h>
#include <ntstatus.h>
#include <ebpf_result.h>

// Mapping from each eBPF result to NTSTATUS
// (and also show the Win32 error code that the NTSTATUS maps to).
// This should be consistent with windows_error_to_ebpf_result()
// in api_common.hpp
static const NTSTATUS _ebpf_result_mapping[] = {
    /* EBPF_SUCCESS */ STATUS_SUCCESS /* ERROR_SUCCESS */,
    /* EBPF_VERIFICATION_FAILED */ STATUS_VERIFIER_STOP /* ERROR_VERIFIER_STOP */,
    /* EBPF_JIT_COMPILATION_FAILED */ STATUS_NONE_MAPPED /* ERROR_NONE_MAPPED */,
    /* EBPF_PROGRAM_LOAD_FAILED */ STATUS_GENERIC_COMMAND_FAILED /* ERROR_GENERIC_COMMAND_FAILED */,
    /* EBPF_INVALID_FD */ STATUS_INVALID_HANDLE /* ERROR_INVALID_HANDLE */,
    /* EBPF_INVALID_OBJECT */ STATUS_INVALID_DEVICE_REQUEST /* ERROR_INVALID_FUNCTION */,
    /* EBPF_INVALID_ARGUMENT */ STATUS_INVALID_PARAMETER /* ERROR_INVALID_PARAMETER */,
    /* EBPF_OBJECT_NOT_FOUND */ STATUS_OBJECT_PATH_NOT_FOUND /* ERROR_PATH_NOT_FOUND */,
    /* EBPF_OBJECT_ALREADY_EXISTS */ STATUS_OBJECTID_EXISTS /* ERROR_OBJECT_ALREADY_EXISTS */,
    /* EBPF_FILE_NOT_FOUND */ STATUS_NO_SUCH_FILE /* ERROR_FILE_NOT_FOUND */,
    /* EBPF_ALREADY_PINNED */ STATUS_OBJECT_NAME_EXISTS /* ERROR_OBJECT_NAME_EXISTS */,
    /* EBPF_NOT_PINNED */ STATUS_RESOURCE_NOT_OWNED /* ERROR_NOT_OWNER */,
    /* EBPF_NO_MEMORY */ STATUS_NO_MEMORY /* ERROR_NOT_ENOUGH_MEMORY */,
    /* EBPF_PROGRAM_TOO_LARGE */ STATUS_TOO_MANY_COMMANDS /* ERROR_TOO_MANY_CMDS */,
    /* EBPF_RPC_EXCEPTION */ RPC_NT_CALL_FAILED /* RPC_S_CALL_FAILED */,
    /* EBPF_ALREADY_INITIALIZED */ STATUS_ALREADY_INITIALIZED /* ERROR_ALREADY_INITIALIZED */,
    /* EBPF_ELF_PARSING_FAILED */ STATUS_INVALID_IMAGE_FORMAT /* ERROR_BAD_EXE_FORMAT */,
    /* EBPF_FAILED */ STATUS_UNSUCCESSFUL /* ERROR_GEN_FAILURE */,
    /* EBPF_OPERATION_NOT_SUPPORTED */ STATUS_NOT_SUPPORTED /* ERROR_NOT_SUPPORTED */,
    /* EBPF_KEY_NOT_FOUND */ STATUS_NOT_FOUND /* ERROR_NOT_FOUND */,
    /* EBPF_ACCESS_DENIED */ STATUS_ACCESS_DENIED /* ERROR_ACCESS_DENIED */,
    /* EBPF_BLOCKED_BY_POLICY */ STATUS_CONTENT_BLOCKED /* ERROR_CONTENT_BLOCKED */,
    /* EBPF_ARITHMETIC_OVERFLOW */ STATUS_INTEGER_OVERFLOW /* ERROR_ARITHMETIC_OVERFLOW */,
    /* EBPF_EXTENSION_FAILED_TO_LOAD */ STATUS_DRIVER_UNABLE_TO_LOAD /* ERROR_BAD_DRIVER */,
    /* EBPF_INSUFFICIENT_BUFFER */ STATUS_BUFFER_OVERFLOW /* ERROR_MORE_DATA */,
    /* EBPF_NO_MORE_KEYS */ STATUS_NO_MORE_MATCHES /* ERROR_NO_MORE_MATCHES */,
    /* EBPF_KEY_ALREADY_EXISTS */
    STATUS_ALREADY_REGISTERED /* ERROR_INTERNAL_ERROR, but ought to be ERROR_ALREADY_REGISTERED */,
    /* EBPF_NO_MORE_TAIL_CALLS */ STATUS_TOO_MANY_NODES /* ERROR_TOO_MANY_NAMES */,
    /* EBPF_PENDING */ STATUS_PENDING /* ERROR_IO_PENDING */,
    /* EBPF_OUT_OF_SPACE */ STATUS_INSUFFICIENT_RESOURCES /* ERROR_NO_SYSTEM_RESOURCES */,
};

NTSTATUS
ebpf_result_to_ntstatus(ebpf_result_t result)
{
    return (result < EBPF_RESULT_COUNT) ? _ebpf_result_mapping[result] : STATUS_UNSUCCESSFUL;
}