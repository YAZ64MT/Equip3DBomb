#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "globalobjects_api.h"
#include "playermodelmanager_api.h"

static Gfx sRecolorableGiBombDL[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 1, PRIM_LOD_FRAC, 1, COMBINED, 0, SHADE, 0, 1, 1,
                       PRIM_LOD_FRAC, 1),
    gsSPEndDisplayList(), // call to middle of bomb GI model here
};

static Mtx s3DBombMtx;

static Gfx s3DBombDL[] = {
    gsSPMatrix(&s3DBombMtx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(sRecolorableGiBombDL),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

GLOBAL_OBJECTS_CALLBACK_ON_READY void onGlobalObjectsReady(void) {
    extern Gfx gGiBombDL[];

    Gfx *giBomb = GlobalObjects_getGlobalGfxPtr(OBJECT_GI_BOMB_1, gGiBombDL);

    gSPBranchList(&sRecolorableGiBombDL[ARRAY_COUNT(sRecolorableGiBombDL) - 1], &giBomb[5]);

    guPosition(&s3DBombMtx, 0.f, 0.f, 0.f, 28.f, 0.f, -0.f, 0.f);
}

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void register3DBomb(void) {
    PlayerModelManagerHandle h = PLAYERMODELMANAGER_REGISTER_MODEL("gi_bomb_as_bomb", PMM_MODEL_TYPE_BOMB);
    PlayerModelManager_setDisplayName(h, "GI Bomb (3D)");
    PlayerModelManager_setAuthor(h, "Nintendo");
    PlayerModelManager_setDisplayList(h, PMM_DL_BOMB_BODY_2D, gEmptyDL);
    PlayerModelManager_setDisplayList(h, PMM_DL_BOMB_CAP, gEmptyDL);
    PlayerModelManager_setDisplayList(h, PMM_DL_BOMB_BODY_3D, s3DBombDL);
}
