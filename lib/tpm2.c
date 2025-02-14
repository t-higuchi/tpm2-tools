/* SPDX-License-Identifier: BSD-3-Clause */

#include <tss2/tss2_mu.h>

#include "log.h"
#include "object.h"
#include "tool_rc.h"
#include "tpm2.h"
#include "tpm2_auth_util.h"

#define TPM2_ERROR_TSS2_RC_ERROR_MASK 0xFFFF

static inline UINT16 tpm2_error_get(TSS2_RC rc) {
    return ((rc & TPM2_ERROR_TSS2_RC_ERROR_MASK));
}

tool_rc tpm2_readpublic(ESYS_CONTEXT *esys_context, ESYS_TR object_handle,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        TPM2B_PUBLIC **out_public, TPM2B_NAME **name,
        TPM2B_NAME **qualified_name) {

    TSS2_RC rval = Esys_ReadPublic(esys_context, object_handle, shandle1,
            shandle2, shandle3, out_public, name, qualified_name);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_ReadPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_from_tpm_public(ESYS_CONTEXT *esys_context, TPM2_HANDLE tpm_handle,
        ESYS_TR optional_session1, ESYS_TR optional_session2,
        ESYS_TR optional_session3, ESYS_TR *object) {

    TSS2_RC rval = Esys_TR_FromTPMPublic(esys_context, tpm_handle,
            optional_session1, optional_session2, optional_session3, object);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_FromTPMPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_tr_deserialize(ESYS_CONTEXT *esys_context, uint8_t const *buffer,
        size_t buffer_size, ESYS_TR *esys_handle) {

    TSS2_RC rval = Esys_TR_Deserialize(esys_context, buffer, buffer_size,
            esys_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_Deserialize, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_tr_serialize(ESYS_CONTEXT *esys_context, ESYS_TR object,
        uint8_t **buffer, size_t *buffer_size) {

    TSS2_RC rval = Esys_TR_Serialize(esys_context, object, buffer, buffer_size);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_Serialize, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_tr_get_name(ESYS_CONTEXT *esys_context, ESYS_TR handle,
        TPM2B_NAME **name) {

    TSS2_RC rval = Esys_TR_GetName(esys_context, handle, name);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_GetName, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_close(ESYS_CONTEXT *esys_context, ESYS_TR *rsrc_handle) {

    TSS2_RC rval = Esys_TR_Close(esys_context, rsrc_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_Close, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nv_readpublic(ESYS_CONTEXT *esys_context, ESYS_TR nv_index,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        TPM2B_NV_PUBLIC **nv_public, TPM2B_NAME **nv_name) {

    TSS2_RC rval = Esys_NV_ReadPublic(esys_context, nv_index, shandle1, shandle2,
            shandle3, nv_public, nv_name);

    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_NV_ReadPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_getcap(ESYS_CONTEXT *esys_context, ESYS_TR shandle1,
        ESYS_TR shandle2, ESYS_TR shandle3, TPM2_CAP capability,
        UINT32 property, UINT32 property_count, TPMI_YES_NO *more_data,
        TPMS_CAPABILITY_DATA **capability_data) {

    TSS2_RC rval = Esys_GetCapability(esys_context, shandle1, shandle2, shandle3,
            capability, property, property_count, more_data, capability_data);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_NV_ReadPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nv_read(ESYS_CONTEXT *esys_context, ESYS_TR auth_handle,
        ESYS_TR nv_index, ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        UINT16 size, UINT16 offset, TPM2B_MAX_NV_BUFFER **data) {

    TSS2_RC rval = Esys_NV_Read(esys_context, auth_handle, nv_index, shandle1,
            shandle2, shandle3, size, offset, data);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_NV_Read, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_context_save(ESYS_CONTEXT *esys_context, ESYS_TR save_handle,
        TPMS_CONTEXT **context) {

    TSS2_RC rval = Esys_ContextSave(esys_context, save_handle, context);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_ContextSave, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_context_load(ESYS_CONTEXT *esys_context,
        const TPMS_CONTEXT *context, ESYS_TR *loaded_handle) {

    TSS2_RC rval = Esys_ContextLoad(esys_context, context, loaded_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_ContextLoad, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_flush_context(ESYS_CONTEXT *esys_context, ESYS_TR flush_handle) {

    TSS2_RC rval = Esys_FlushContext(esys_context, flush_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_FlushContext, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_start_auth_session(ESYS_CONTEXT *esys_context, ESYS_TR tpm_key,
        ESYS_TR bind, ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPM2B_NONCE *nonce_caller, TPM2_SE session_type,
        const TPMT_SYM_DEF *symmetric, TPMI_ALG_HASH auth_hash,
        ESYS_TR *session_handle) {

    TSS2_RC rval = Esys_StartAuthSession(esys_context, tpm_key, bind, shandle1,
            shandle2, shandle3, nonce_caller, session_type, symmetric,
            auth_hash, session_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_StartAuthSession, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_sess_set_attributes(ESYS_CONTEXT *esys_context, ESYS_TR session,
        TPMA_SESSION flags, TPMA_SESSION mask) {

    TSS2_RC rval = Esys_TRSess_SetAttributes(esys_context, session, flags, mask);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TRSess_SetAttributes, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_sess_get_attributes(ESYS_CONTEXT *esys_context, ESYS_TR session,
        TPMA_SESSION *flags) {

    TSS2_RC rval = Esys_TRSess_GetAttributes(esys_context, session, flags);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_TRSess_GetAttributes, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_restart(ESYS_CONTEXT *esys_context, ESYS_TR session_handle,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3) {

    TSS2_RC rval = Esys_PolicyRestart(esys_context, session_handle, shandle1,
            shandle2, shandle3);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyRestart, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_get_capability(ESYS_CONTEXT *esys_context, ESYS_TR shandle1,
        ESYS_TR shandle2, ESYS_TR shandle3, TPM2_CAP capability,
        UINT32 property, UINT32 property_count, TPMI_YES_NO *more_data,
        TPMS_CAPABILITY_DATA **capability_data) {

    TSS2_RC rval = Esys_GetCapability(esys_context, shandle1, shandle2, shandle3,
            capability, property, property_count, more_data, capability_data);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_GetCapability, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_create_primary(ESYS_CONTEXT *esys_context, ESYS_TR primary_handle,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPM2B_SENSITIVE_CREATE *in_sensitive, const TPM2B_PUBLIC *in_public,
        const TPM2B_DATA *outside_info, const TPML_PCR_SELECTION *creation_pcr,
        ESYS_TR *object_handle, TPM2B_PUBLIC **out_public,
        TPM2B_CREATION_DATA **creation_data, TPM2B_DIGEST **creation_hash,
        TPMT_TK_CREATION **creation_ticket) {

    TSS2_RC rval = Esys_CreatePrimary(esys_context, primary_handle, shandle1,
            shandle2, shandle3, in_sensitive, in_public, outside_info, creation_pcr,
            object_handle, out_public, creation_data, creation_hash,
            creation_ticket);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_CreatePrimary, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_pcr_read(ESYS_CONTEXT *esys_context, ESYS_TR shandle1,
        ESYS_TR shandle2, ESYS_TR shandle3,
        const TPML_PCR_SELECTION *pcr_selection_in, UINT32 *pcr_update_counter,
        TPML_PCR_SELECTION **pcr_selection_out, TPML_DIGEST **pcr_values) {

    TSS2_RC rval = Esys_PCR_Read(esys_context, shandle1, shandle2, shandle3,
            pcr_selection_in, pcr_update_counter, pcr_selection_out, pcr_values);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PCR_Read, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_authorize(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPM2B_DIGEST *approved_policy, const TPM2B_NONCE *policy_ref,
        const TPM2B_NAME *key_sign, const TPMT_TK_VERIFIED *check_ticket) {

    TSS2_RC rval = Esys_PolicyAuthorize(esys_context, policy_session, shandle1,
            shandle2, shandle3, approved_policy, policy_ref, key_sign,
            check_ticket);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyAuthorize, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_or(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPML_DIGEST *p_hash_list) {

    TSS2_RC rval = Esys_PolicyOR(esys_context, policy_session, shandle1, shandle2,
            shandle3, p_hash_list);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyAuthorize, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_pcr(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPM2B_DIGEST *pcr_digest, const TPML_PCR_SELECTION *pcrs) {

    TSS2_RC rval = Esys_PolicyPCR(esys_context, policy_session, shandle1,
            shandle2, shandle3, pcr_digest, pcrs);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyPCR, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_password(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3) {

    TSS2_RC rval = Esys_PolicyPassword(esys_context, policy_session, shandle1,
            shandle2, shandle3);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyPassword, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_secret(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_entity_obj, ESYS_TR policy_session) {

    const TPM2B_NONCE *nonce_tpm = NULL;
    const TPM2B_DIGEST *cp_hash_a = NULL;
    const TPM2B_NONCE *policy_ref = NULL;
    INT32 expiration = 0;
    TPM2B_TIMEOUT **timeout = NULL;
    TPMT_TK_AUTH **policy_ticket = NULL;

    ESYS_TR auth_entity_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_entity_obj->tr_handle, auth_entity_obj->session,
            &auth_entity_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get auth entity obj session");
        return rc;
    }

    TSS2_RC rval = Esys_PolicySecret(esys_context, auth_entity_obj->tr_handle,
            policy_session, auth_entity_obj_session_handle, ESYS_TR_NONE,
            ESYS_TR_NONE, nonce_tpm, cp_hash_a, policy_ref, expiration, timeout,
            policy_ticket);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicySecret, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_getdigest(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        TPM2B_DIGEST **policy_digest) {

    TSS2_RC rval = Esys_PolicyGetDigest(esys_context, policy_session, shandle1,
            shandle2, shandle3, policy_digest);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyGetDigest, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_command_code(ESYS_CONTEXT *esys_context,
        ESYS_TR policy_session, ESYS_TR shandle1, ESYS_TR shandle2,
        ESYS_TR shandle3, TPM2_CC code) {

    TSS2_RC rval = Esys_PolicyCommandCode(esys_context, policy_session, shandle1,
            shandle2, shandle3, code);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyCommandCode, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_locality(ESYS_CONTEXT *esys_context, ESYS_TR policy_session,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        TPMA_LOCALITY locality) {

    TSS2_RC rval = Esys_PolicyLocality(esys_context, policy_session, shandle1,
            shandle2, shandle3, locality);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyLocality, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_policy_duplication_select(ESYS_CONTEXT *esys_context,
        ESYS_TR policy_session, ESYS_TR shandle1, ESYS_TR shandle2,
        ESYS_TR shandle3, const TPM2B_NAME *object_name,
        const TPM2B_NAME *new_parent_name, TPMI_YES_NO include_object) {

    TSS2_RC rval = Esys_PolicyDuplicationSelect(esys_context, policy_session,
            shandle1, shandle2, shandle3, object_name, new_parent_name,
            include_object);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_PolicyDuplicationSelect, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_mu_tpm2_handle_unmarshal(uint8_t const buffer[], size_t size,
        size_t *offset, TPM2_HANDLE *out) {

    TSS2_RC rval = Tss2_MU_TPM2_HANDLE_Unmarshal(buffer, size, offset, out);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Tss2_MU_TPM2_HANDLE_Unmarshal, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_mu_tpmt_public_marshal(TPMT_PUBLIC const *src, uint8_t buffer[],
        size_t buffer_size, size_t *offset) {

    TSS2_RC rval = Tss2_MU_TPMT_PUBLIC_Marshal(src, buffer, buffer_size,
            offset);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Tss2_MU_TPMT_PUBLIC_Marshal, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_evictcontrol(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj,
        tpm2_loaded_object *to_persist_key_obj,
        TPMI_DH_PERSISTENT persistent_handle, ESYS_TR *new_object_handle) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_EvictControl(esys_context, auth_hierarchy_obj->tr_handle,
            to_persist_key_obj->tr_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE,
            persistent_handle, new_object_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_EvictControl, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hash(ESYS_CONTEXT *esys_context, ESYS_TR shandle1, ESYS_TR shandle2,
        ESYS_TR shandle3, const TPM2B_MAX_BUFFER *data, TPMI_ALG_HASH hash_alg,
        TPMI_RH_HIERARCHY hierarchy, TPM2B_DIGEST **out_hash,
        TPMT_TK_HASHCHECK **validation) {

    TSS2_RC rval = Esys_Hash(esys_context, shandle1, shandle2, shandle3, data,
            hash_alg, hierarchy, out_hash, validation);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_Hash, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hash_sequence_start(ESYS_CONTEXT *esys_context, ESYS_TR shandle1,
        ESYS_TR shandle2, ESYS_TR shandle3, const TPM2B_AUTH *auth,
        TPMI_ALG_HASH hash_alg, ESYS_TR *sequence_handle) {

    TSS2_RC rval = Esys_HashSequenceStart(esys_context, shandle1, shandle2,
            shandle3, auth, hash_alg, sequence_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HashSequenceStart, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_sequence_update(ESYS_CONTEXT *esys_context, ESYS_TR sequence_handle,
        ESYS_TR shandle1, ESYS_TR shandle2, ESYS_TR shandle3,
        const TPM2B_MAX_BUFFER *buffer) {

    TSS2_RC rval = Esys_SequenceUpdate(esys_context, sequence_handle, shandle1,
            shandle2, shandle3, buffer);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_SequenceUpdate, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_sequence_complete(ESYS_CONTEXT *esys_context,
        ESYS_TR sequence_handle, ESYS_TR shandle1, ESYS_TR shandle2,
        ESYS_TR shandle3, const TPM2B_MAX_BUFFER *buffer,
        TPMI_RH_HIERARCHY hierarchy, TPM2B_DIGEST **result,
        TPMT_TK_HASHCHECK **validation) {

    TSS2_RC rval = Esys_SequenceComplete(esys_context, sequence_handle, shandle1,
            shandle2, shandle3, buffer, hierarchy, result, validation);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_SequenceComplete, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_tr_set_auth(ESYS_CONTEXT *esys_context, ESYS_TR handle,
        TPM2B_AUTH const *auth_value) {

    TSS2_RC rval = Esys_TR_SetAuth(esys_context, handle, auth_value);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_SequenceComplete, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_activatecredential(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *activatehandleobj, tpm2_loaded_object *keyhandleobj,
        const TPM2B_ID_OBJECT *credential_blob,
        const TPM2B_ENCRYPTED_SECRET *secret, TPM2B_DIGEST **cert_info) {

    ESYS_TR keyobj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            keyhandleobj->tr_handle, keyhandleobj->session,
            &keyobj_session_handle); //shandle1
    if (rc != tool_rc_success) {
        return rc;
    }

    ESYS_TR activateobj_session_handle = ESYS_TR_NONE;
    rc = tpm2_auth_util_get_shandle(esys_context, activatehandleobj->tr_handle,
            activatehandleobj->session, &activateobj_session_handle);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_ActivateCredential(esys_context,
            activatehandleobj->tr_handle, keyhandleobj->tr_handle,
            activateobj_session_handle, keyobj_session_handle, ESYS_TR_NONE,
            credential_blob, secret, cert_info);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_ActivateCredential, rval);
        rc = tool_rc_from_tpm(rval);
        return rc;
    }

    return tool_rc_success;
}

tool_rc tpm2_create(ESYS_CONTEXT *esys_context, tpm2_loaded_object *parent_obj,
        const TPM2B_SENSITIVE_CREATE *in_sensitive, const TPM2B_PUBLIC *in_public,
        const TPM2B_DATA *outside_info, const TPML_PCR_SELECTION *creation_pcr,
        TPM2B_PRIVATE **out_private, TPM2B_PUBLIC **out_public,
        TPM2B_CREATION_DATA **creation_data, TPM2B_DIGEST **creation_hash,
        TPMT_TK_CREATION **creation_ticket) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, parent_obj->tr_handle,
            parent_obj->session, &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_Create(esys_context, parent_obj->tr_handle, shandle1,
            ESYS_TR_NONE, ESYS_TR_NONE, in_sensitive, in_public, outside_info,
            creation_pcr, out_private, out_public, creation_data, creation_hash,
            creation_ticket);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_Create, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_create_loaded(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *parent_obj,
        const TPM2B_SENSITIVE_CREATE *in_sensitive,
        const TPM2B_TEMPLATE *in_public, ESYS_TR *object_handle,
        TPM2B_PRIVATE **out_private, TPM2B_PUBLIC **out_public) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, parent_obj->tr_handle,
            parent_obj->session, &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_CreateLoaded(esys_context, parent_obj->tr_handle,
            shandle1, ESYS_TR_NONE, ESYS_TR_NONE, in_sensitive, in_public,
            object_handle, out_private, out_public);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_CreateLoaded, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_object_change_auth(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *parent_object, tpm2_loaded_object *object,
        const TPM2B_AUTH *new_auth, TPM2B_PRIVATE **out_private) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, object->tr_handle,
            object->session, &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_ObjectChangeAuth(esys_context, object->tr_handle,
            parent_object->tr_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE,
            new_auth, out_private);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_ObjectChangeAuth, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nv_change_auth(ESYS_CONTEXT *esys_context, tpm2_loaded_object *nv,
        const TPM2B_AUTH *new_auth) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, nv->tr_handle,
            nv->session, &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_NV_ChangeAuth(esys_context, nv->tr_handle, shandle1,
            ESYS_TR_NONE, ESYS_TR_NONE, new_auth);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_NV_ChangeAuth, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hierarchy_change_auth(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *hierarchy, const TPM2B_AUTH *new_auth) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, hierarchy->tr_handle,
            hierarchy->session, &shandle1);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_HierarchyChangeAuth(esys_context, hierarchy->tr_handle,
            shandle1, ESYS_TR_NONE, ESYS_TR_NONE, new_auth);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_HierarchyChangeAuth, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_certify(ESYS_CONTEXT *ectx, tpm2_loaded_object *certifiedkey_obj,
        tpm2_loaded_object *signingkey_obj, TPM2B_DATA *qualifying_data,
        TPMT_SIG_SCHEME *scheme, TPM2B_ATTEST **certify_info,
        TPMT_SIGNATURE **signature) {

    ESYS_TR certifiedkey_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(ectx, certifiedkey_obj->tr_handle,
            certifiedkey_obj->session, &certifiedkey_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get session handle for TPM object");
        return rc;
    }

    ESYS_TR signingkey_session_handle = ESYS_TR_NONE;
    rc = tpm2_auth_util_get_shandle(ectx, signingkey_obj->tr_handle,
            signingkey_obj->session, &signingkey_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get session handle for key");
        return rc;
    }

    TSS2_RC rval = Esys_Certify(ectx, certifiedkey_obj->tr_handle,
            signingkey_obj->tr_handle, certifiedkey_session_handle,
            signingkey_session_handle, ESYS_TR_NONE, qualifying_data, scheme,
            certify_info, signature);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Eys_Certify, rval);
        rc = tool_rc_from_tpm(rval);
        return rc;
    }

    return tool_rc_success;
}

tool_rc tpm2_rsa_decrypt(ESYS_CONTEXT *ectx, tpm2_loaded_object *keyobj,
        const TPM2B_PUBLIC_KEY_RSA *cipher_text, const TPMT_RSA_DECRYPT *scheme,
        const TPM2B_DATA *label, TPM2B_PUBLIC_KEY_RSA **message) {

    ESYS_TR keyobj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(ectx, keyobj->tr_handle,
            keyobj->session, &keyobj_session_handle);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_RSA_Decrypt(ectx, keyobj->tr_handle,
            keyobj_session_handle, ESYS_TR_NONE, ESYS_TR_NONE, cipher_text,
            scheme, label, message);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_RSA_Decrypt, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_load(ESYS_CONTEXT *esys_context, tpm2_loaded_object *parentobj,
        const TPM2B_PRIVATE *in_private, const TPM2B_PUBLIC *in_public,
        ESYS_TR *object_handle) {

    ESYS_TR parent_object_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, parentobj->tr_handle,
            parentobj->session, &parent_object_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get parent object session handle");
        return rc;
    }

    TSS2_RC rval = Esys_Load(esys_context, parentobj->tr_handle,
            parent_object_session_handle, ESYS_TR_NONE, ESYS_TR_NONE, in_private,
            in_public, object_handle);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Eys_Load, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_clear(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy->tr_handle, auth_hierarchy->session, &shandle1);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle for hierarchy");
        return rc;
    }

    TSS2_RC rval = Esys_Clear(esys_context, auth_hierarchy->tr_handle, shandle1,
            ESYS_TR_NONE, ESYS_TR_NONE);
    if (rval != TPM2_RC_SUCCESS && rval != TPM2_RC_INITIALIZE) {
        LOG_PERR(Esys_Clear, rval);
        return tool_rc_from_tpm(rval);
    }
    return tool_rc_success;
}

tool_rc tpm2_clearcontrol(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy, TPMI_YES_NO disable_clear) {

    ESYS_TR shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy->tr_handle, auth_hierarchy->session, &shandle);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_ClearControl(esys_context, auth_hierarchy->tr_handle,
            shandle, ESYS_TR_NONE, ESYS_TR_NONE, disable_clear);
    if (rval != TPM2_RC_SUCCESS && rval != TPM2_RC_INITIALIZE) {
        LOG_PERR(Esys_ClearControl, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_dictionarylockout(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy,
        bool clear_lockout,
        bool setup_parameters, UINT32 max_tries, UINT32 recovery_time,
        UINT32 lockout_recovery_time) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy->tr_handle, auth_hierarchy->session, &shandle1);
    if (rc != tool_rc_success) {
        LOG_ERR("Couldn't get shandle for lockout hierarchy");
        return rc;
    }

    /*
     * If setup params and clear lockout are both required, clear lockout should
     * precede parameters setup.
     */
    TPM2_RC rval;
    if (clear_lockout) {
        LOG_INFO("Resetting dictionary lockout state.");
        rval = Esys_DictionaryAttackLockReset(esys_context,
                auth_hierarchy->tr_handle, shandle1, ESYS_TR_NONE,
                ESYS_TR_NONE);
        if (rval != TPM2_RC_SUCCESS) {
            LOG_PERR(Esys_DictionaryAttackLockReset, rval);
            return tool_rc_from_tpm(rval);
        }
    }

    if (setup_parameters) {
        LOG_INFO("Setting up Dictionary Lockout parameters.");
        rval = Esys_DictionaryAttackParameters(esys_context,
                auth_hierarchy->tr_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE,
                max_tries, recovery_time, lockout_recovery_time);
        if (rval != TPM2_RC_SUCCESS) {
            LOG_PERR(Esys_DictionaryAttackParameters, rval);
            return tool_rc_from_tpm(rval);
        }
    }

    return tool_rc_success;
}

tool_rc tpm2_duplicate(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *duplicable_key, ESYS_TR new_parent_handle,
        const TPM2B_DATA *in_key, const TPMT_SYM_DEF_OBJECT *sym_alg,
        TPM2B_DATA **out_key, TPM2B_PRIVATE **duplicate,
        TPM2B_ENCRYPTED_SECRET **encrypted_seed) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            duplicable_key->tr_handle, duplicable_key->session, &shandle1);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    TSS2_RC rval = Esys_Duplicate(esys_context, duplicable_key->tr_handle,
            new_parent_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE, in_key,
            sym_alg, out_key, duplicate, encrypted_seed);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_Duplicate, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_encryptdecrypt(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *encryption_key_obj, TPMI_YES_NO decrypt,
        TPMI_ALG_SYM_MODE mode, const TPM2B_IV *iv_in,
        const TPM2B_MAX_BUFFER *input_data, TPM2B_MAX_BUFFER **output_data,
        TPM2B_IV **iv_out, ESYS_TR shandle1, unsigned *version) {

    TSS2_RC rval = Esys_EncryptDecrypt2(esys_context,
            encryption_key_obj->tr_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE,
            input_data, decrypt, mode, iv_in, output_data, iv_out);
    if (tpm2_error_get(rval) == TPM2_RC_COMMAND_CODE) {
        *version = 1;
        rval = Esys_EncryptDecrypt(esys_context, encryption_key_obj->tr_handle,
                shandle1, ESYS_TR_NONE, ESYS_TR_NONE, decrypt, mode, iv_in,
                input_data, output_data, iv_out);
    }

    if (rval != TPM2_RC_SUCCESS) {
        if (*version == 2) {
            LOG_PERR(Esys_EncryptDecrypt2, rval);
        } else {
            LOG_PERR(Esys_EncryptDecrypt, rval);
        }
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hierarchycontrol(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy, TPMI_RH_ENABLES enable,
        TPMI_YES_NO state) {

    ESYS_TR shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy->tr_handle, auth_hierarchy->session, &shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle for hierarchy");
        return rc;
    }

    TSS2_RC rval = Esys_HierarchyControl(esys_context, auth_hierarchy->tr_handle,
            shandle, ESYS_TR_NONE, ESYS_TR_NONE, enable, state);
    if (rval != TPM2_RC_SUCCESS && rval != TPM2_RC_INITIALIZE) {
        LOG_PERR(Esys_HierarchyControl, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hmac(ESYS_CONTEXT *esys_context, tpm2_loaded_object *hmac_key_obj,
        TPMI_ALG_HASH halg, const TPM2B_MAX_BUFFER *input_buffer,
        TPM2B_DIGEST **out_hmac) {

    ESYS_TR hmac_key_obj_shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            hmac_key_obj->tr_handle, hmac_key_obj->session,
            &hmac_key_obj_shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get hmac_key_obj_shandle");
        return rc;
    }

    TPM2_RC rval = Esys_HMAC(esys_context, hmac_key_obj->tr_handle,
            hmac_key_obj_shandle, ESYS_TR_NONE, ESYS_TR_NONE, input_buffer,
            halg, out_hmac);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HMAC, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hmac_start(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *hmac_key_obj, TPMI_ALG_HASH halg,
        ESYS_TR *sequence_handle) {

    ESYS_TR hmac_key_obj_shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            hmac_key_obj->tr_handle, hmac_key_obj->session,
            &hmac_key_obj_shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get hmac_key_obj_shandle");
        return rc;
    }

    TPM2B_AUTH null_auth = { .size = 0 };
    TPM2_RC rval = Esys_HMAC_Start(esys_context, hmac_key_obj->tr_handle,
            hmac_key_obj_shandle, ESYS_TR_NONE, ESYS_TR_NONE, &null_auth, halg,
            sequence_handle);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HMAC, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hmac_sequenceupdate(ESYS_CONTEXT *esys_context,
        ESYS_TR sequence_handle, tpm2_loaded_object *hmac_key_obj,
        const TPM2B_MAX_BUFFER *input_buffer) {

    ESYS_TR hmac_key_obj_shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            hmac_key_obj->tr_handle, hmac_key_obj->session,
            &hmac_key_obj_shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get hmac_key_obj_shandle");
        return rc;
    }

    TPM2_RC rval = Esys_SequenceUpdate(esys_context, sequence_handle,
            hmac_key_obj_shandle, ESYS_TR_NONE, ESYS_TR_NONE, input_buffer);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HMAC, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_hmac_sequencecomplete(ESYS_CONTEXT *esys_context,
        ESYS_TR sequence_handle, tpm2_loaded_object *hmac_key_obj,
        const TPM2B_MAX_BUFFER *input_buffer, TPM2B_DIGEST **result,
        TPMT_TK_HASHCHECK **validation) {

    ESYS_TR hmac_key_obj_shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            hmac_key_obj->tr_handle, hmac_key_obj->session,
            &hmac_key_obj_shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get hmac_key_obj_shandle");
        return rc;
    }

    TPM2_RC rval = Esys_SequenceComplete(esys_context, sequence_handle,
            hmac_key_obj_shandle, ESYS_TR_NONE, ESYS_TR_NONE, input_buffer,
            TPM2_RH_NULL, result, validation);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HMAC, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_import(ESYS_CONTEXT *esys_context, tpm2_loaded_object *parent_obj,
        const TPM2B_DATA *encryption_key, const TPM2B_PUBLIC *object_public,
        const TPM2B_PRIVATE *duplicate, const TPM2B_ENCRYPTED_SECRET *in_sym_seed,
        const TPMT_SYM_DEF_OBJECT *symmetric_alg, TPM2B_PRIVATE **out_private) {

    ESYS_TR parentobj_shandle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, parent_obj->tr_handle,
            parent_obj->session, &parentobj_shandle);
    if (rc != tool_rc_success) {
        LOG_ERR("Couldn't get shandle for phandle");
        return rc;
    }

    TPM2_RC rval = Esys_Import(esys_context, parent_obj->tr_handle,
            parentobj_shandle, ESYS_TR_NONE, ESYS_TR_NONE, encryption_key,
            object_public, duplicate, in_sym_seed, symmetric_alg, out_private);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_PERR(Esys_HMAC, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nv_definespace(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj, const TPM2B_AUTH *auth,
        const TPM2B_NV_PUBLIC *public_info) {

    ESYS_TR shandle1 = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &shandle1);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    ESYS_TR nvHandle;
    TSS2_RC rval = Esys_NV_DefineSpace(esys_context,
            auth_hierarchy_obj->tr_handle, shandle1, ESYS_TR_NONE, ESYS_TR_NONE,
            auth, public_info, &nvHandle);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_ERR("Failed to define NV area at index 0x%X",
                public_info->nvPublic.nvIndex);
        LOG_PERR(Esys_NV_DefineSpace, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nv_increment(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj, TPM2_HANDLE nv_index) {

    ESYS_TR auth_hierarchy_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &auth_hierarchy_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    // Convert TPM2_HANDLE ctx.nv_index to an ESYS_TR
    ESYS_TR esys_tr_nv_index;
    TSS2_RC rval = Esys_TR_FromTPMPublic(esys_context, nv_index, ESYS_TR_NONE,
            ESYS_TR_NONE, ESYS_TR_NONE, &esys_tr_nv_index);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_FromTPMPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    rval = Esys_NV_Increment(esys_context, auth_hierarchy_obj->tr_handle,
            esys_tr_nv_index, auth_hierarchy_obj_session_handle, ESYS_TR_NONE,
            ESYS_TR_NONE);
    if (rval != TPM2_RC_SUCCESS) {
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nvreadlock(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj, TPM2_HANDLE nv_index) {

    ESYS_TR esys_tr_nv_handle;
    TSS2_RC rval = Esys_TR_FromTPMPublic(esys_context, nv_index, ESYS_TR_NONE,
            ESYS_TR_NONE, ESYS_TR_NONE, &esys_tr_nv_handle);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_FromTPMPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    ESYS_TR auth_hierarchy_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &auth_hierarchy_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    rval = Esys_NV_ReadLock(esys_context, auth_hierarchy_obj->tr_handle,
            esys_tr_nv_handle, auth_hierarchy_obj_session_handle, ESYS_TR_NONE,
            ESYS_TR_NONE);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_ERR("Failed to lock NVRAM area at index 0x%X", nv_index);
        LOG_PERR(Esys_NV_ReadLock, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_nvundefine(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj, TPM2_HANDLE nv_index) {

    ESYS_TR esys_tr_nv_handle;
    TSS2_RC rval = Esys_TR_FromTPMPublic(esys_context, nv_index, ESYS_TR_NONE,
            ESYS_TR_NONE, ESYS_TR_NONE, &esys_tr_nv_handle);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_FromTPMPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    ESYS_TR auth_hierarchy_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &auth_hierarchy_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Couldn't get shandle");
        return rc;
    }

    rval = Esys_NV_UndefineSpace(esys_context, auth_hierarchy_obj->tr_handle,
            esys_tr_nv_handle, auth_hierarchy_obj_session_handle, ESYS_TR_NONE,
            ESYS_TR_NONE);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_ERR("Failed to release NV area at index 0x%X", nv_index);
        LOG_PERR(Esys_NV_UndefineSpace, rval);
        return tool_rc_from_tpm(rval);
    }

    LOG_INFO("Success to release NV area at index 0x%x.", nv_index);

    return tool_rc_success;
}

tool_rc tpm2_nvwrite(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj, TPM2_HANDLE nvindex,
        const TPM2B_MAX_NV_BUFFER *data, UINT16 offset) {

    // Convert TPM2_HANDLE ctx.nv_index to an ESYS_TR
    ESYS_TR esys_tr_nv_index;
    TSS2_RC rval = Esys_TR_FromTPMPublic(esys_context, nvindex, ESYS_TR_NONE,
            ESYS_TR_NONE, ESYS_TR_NONE, &esys_tr_nv_index);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_TR_FromTPMPublic, rval);
        return tool_rc_from_tpm(rval);
    }

    ESYS_TR auth_hierarchy_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            auth_hierarchy_obj->tr_handle, auth_hierarchy_obj->session,
            &auth_hierarchy_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    rval = Esys_NV_Write(esys_context, auth_hierarchy_obj->tr_handle,
            esys_tr_nv_index, auth_hierarchy_obj_session_handle, ESYS_TR_NONE,
            ESYS_TR_NONE, data, offset);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_ERR("Failed to write NV area at index 0x%X", nvindex);
        LOG_PERR(Tss2_Sys_NV_Write, rval);
        return tool_rc_from_tpm(rval);
    }

    LOG_INFO("Success to write NV area at index 0x%x offset 0x%x.", nvindex,
            offset);
    return tool_rc_success;
}

tool_rc tpm2_pcr_allocate(ESYS_CONTEXT *esys_context,
        tpm2_loaded_object *auth_hierarchy_obj,
        const TPML_PCR_SELECTION *pcr_allocation) {

    TSS2_RC rval;
    TPMI_YES_NO allocation_success;
    UINT32 max_pcr;
    UINT32 size_needed;
    UINT32 size_available;

    ESYS_TR auth_hierarchy_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, ESYS_TR_RH_PLATFORM,
            auth_hierarchy_obj->session, &auth_hierarchy_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Couldn't get shandle for lockout hierarchy");
        return rc;
    }

    rval = Esys_PCR_Allocate(esys_context, ESYS_TR_RH_PLATFORM,
            auth_hierarchy_obj_session_handle, ESYS_TR_NONE, ESYS_TR_NONE,
            pcr_allocation, &allocation_success, &max_pcr, &size_needed,
            &size_available);
    if (rval != TSS2_RC_SUCCESS) {
        LOG_ERR("Could not allocate PCRs.");
        LOG_PERR(Esys_PCR_Allocate, rval);
        return tool_rc_from_tpm(rval);
    }

    if (!allocation_success) {
        LOG_ERR("Allocation failed. "
                "MaxPCR: %i, Size Needed: %i, Size available: %i", max_pcr,
                size_needed, size_available);
        return tool_rc_general_error;
    }

    return tool_rc_success;
}

tool_rc tpm2_sign(ESYS_CONTEXT *esys_context, tpm2_loaded_object *signingkey_obj,
        TPM2B_DIGEST *digest, TPMT_SIG_SCHEME *in_scheme,
        TPMT_TK_HASHCHECK *validation, TPMT_SIGNATURE **signature) {

    ESYS_TR signingkey_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context,
            signingkey_obj->tr_handle, signingkey_obj->session,
            &signingkey_obj_session_handle);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_Sign(esys_context, signingkey_obj->tr_handle,
            signingkey_obj_session_handle, ESYS_TR_NONE, ESYS_TR_NONE, digest,
            in_scheme, validation, signature);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Eys_Sign, rval);
        rc = tool_rc_from_tpm(rval);
        return rc;
    }

    return tool_rc_success;
}

tool_rc tpm2_quote(ESYS_CONTEXT *esys_context, tpm2_loaded_object *quote_obj,
        TPMT_SIG_SCHEME *in_scheme, TPM2B_DATA *qualifying_data,
        TPML_PCR_SELECTION *pcr_select, TPM2B_ATTEST **quoted,
        TPMT_SIGNATURE **signature) {

    ESYS_TR quote_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, quote_obj->tr_handle,
            quote_obj->session, &quote_obj_session_handle);
    if (rc != tool_rc_success) {
        LOG_ERR("Failed to get shandle");
        return rc;
    }

    TSS2_RC rval = Esys_Quote(esys_context, quote_obj->tr_handle,
            quote_obj_session_handle, ESYS_TR_NONE, ESYS_TR_NONE,
            qualifying_data, in_scheme, pcr_select, quoted, signature);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_Quote, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}

tool_rc tpm2_unseal(ESYS_CONTEXT *esys_context, tpm2_loaded_object *sealkey_obj,
        TPM2B_SENSITIVE_DATA **out_data) {

    ESYS_TR sealkey_obj_session_handle = ESYS_TR_NONE;
    tool_rc rc = tpm2_auth_util_get_shandle(esys_context, sealkey_obj->tr_handle,
            sealkey_obj->session, &sealkey_obj_session_handle);
    if (rc != tool_rc_success) {
        return rc;
    }

    TSS2_RC rval = Esys_Unseal(esys_context, sealkey_obj->tr_handle,
            sealkey_obj_session_handle, ESYS_TR_NONE, ESYS_TR_NONE, out_data);
    if (rval != TPM2_RC_SUCCESS) {
        LOG_PERR(Esys_Unseal, rval);
        return tool_rc_from_tpm(rval);
    }

    return tool_rc_success;
}
