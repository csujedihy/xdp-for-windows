//
// Copyright (C) Microsoft Corporation. All rights reserved.
//

#pragma once

#include "oid.h"

//
// Hardware RSS capabilities.
//
typedef struct XDP_LWF_RSS {
    ULONG MaxReceiveQueueCount;
} XDP_LWF_RSS;

//
// Describes a set of interface offload configurations.
//
typedef struct _XDP_LWF_INTERFACE_OFFLOAD_SETTINGS {
    XDP_OFFLOAD_PARAMS_RSS *Rss;
    // ...
} XDP_LWF_INTERFACE_OFFLOAD_SETTINGS;

//
// Per LWF filter state.
//
typedef struct _XDP_LWF_OFFLOAD {
    XDP_LWF_RSS Rss;
    XDP_LWF_INTERFACE_OFFLOAD_SETTINGS UpperEdge;
    XDP_LWF_INTERFACE_OFFLOAD_SETTINGS LowerEdge;
    LIST_ENTRY InterfaceOffloadHandleListHead;
} XDP_LWF_OFFLOAD;

inline
BOOLEAN
XdpLwfOffloadIsNdisRssEnabled(
    _In_ CONST NDIS_RECEIVE_SCALE_PARAMETERS *NdisRssParams
    )
{
    return
        NDIS_RSS_HASH_FUNC_FROM_HASH_INFO(NdisRssParams->HashInformation) != 0 &&
        (NdisRssParams->Flags & NDIS_RSS_PARAM_FLAG_DISABLE_RSS) == 0;
}

NDIS_STATUS
XdpLwfOffloadInspectOidRequest(
    _In_ XDP_LWF_FILTER *Filter,
    _In_ NDIS_OID_REQUEST *Request,
    _Out_ XDP_OID_ACTION *Action,
    _Out_ NDIS_STATUS *CompletionStatus
    );

VOID
XdpLwfOffloadTransformNbls(
    _In_ XDP_LWF_FILTER *Filter,
    _Inout_ NBL_COUNTED_QUEUE *NblList,
    _In_ UINT32 XdpInspectFlags
    );

VOID
XdpLwfOffloadInitialize(
    _In_ XDP_LWF_FILTER *Filter
    );

VOID
XdpLwfOffloadUnInitialize(
    _In_ XDP_LWF_FILTER *Filter
    );

extern CONST XDP_OFFLOAD_DISPATCH XdpLwfOffloadDispatch;