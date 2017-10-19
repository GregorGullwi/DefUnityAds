#define EXTENSION_NAME DefUnityAds
#define LIB_NAME "DefUnityAds"
#define MODULE_NAME "unityads"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "utils/LuaUtils.h"
#include "DefUnityCallback.h"

#if defined(DM_PLATFORM_IOS)
#include "objc/DefUnityAdsIOS.h"
#elif defined(DM_PLATFORM_ANDROID)
#include "andrcpp/DefUnityAdsAndr.h"
#endif

static int Initialize(lua_State* L) {
    const char *gameId_lua = luaL_checkstring(L, 1);
    bool enableDebugMode_lua = false;
    set_callback(L, 2);
    if (lua_type(L, 3) != LUA_TNONE){
        enableDebugMode_lua = luaL_checkbool(L, 3);
    }
    //DefUnityAds_Initialize(gameId_lua, enableDebugMode_lua);
    return 0;
}

static int Show(lua_State* L) {
	char *placementId_lua = "";
    if (lua_type(L, 1) != LUA_TNONE){
		placementId_lua = (char*)luaL_checkstring(L, 1);
    }
    //DefUnityAds_Show(placementId_lua);
    return 0;
}

static int isReady(lua_State* L) {
    char *placementId_lua = "";
    if (lua_type(L, 1) != LUA_TNONE){
        placementId_lua = (char*)luaL_checkstring(L, 1);
    }
    bool status = false;//DefUnityAds_isReady(placementId_lua);
    lua_pushboolean(L, status);
    return 1;
}

static int isInitialized(lua_State* L) {
    bool status = DefUnityAds_isInitialized();
    lua_pushboolean(L, status);
    return 1;
}

static int isSupported(lua_State* L) {
    bool status = DefUnityAds_isSupported();
    lua_pushboolean(L, status);
    return 1;
}

static int getDebugMode(lua_State* L) {
    bool status = DefUnityAds_getDebugMode();
    lua_pushboolean(L, status);
    return 1;
}

static int getVersion(lua_State* L) {
    const char *version = DefUnityAds_getVersion();
    lua_pushstring(L, version);
    return 1;
}

static int setDebugMode(lua_State* L) {
    bool enableDebugMode_lua = luaL_checkbool(L, 1);
    DefUnityAds_setDebugMode(enableDebugMode_lua);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Initialize},
    {"show", Show},
    {"isReady", isReady},
    {"isSupported", isSupported},
    {"isInitialized", isInitialized},
    {"getDebugMode", getDebugMode},
    {"getVersion", getVersion},
    {"setDebugMode", setDebugMode},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
lua_pushnumber(L, (lua_Number) name); \
lua_setfield(L, -2, #name);\

    SETCONSTANT(TYPE_IS_READY)
    SETCONSTANT(TYPE_DID_START)
    SETCONSTANT(TYPE_DID_ERROR)
    SETCONSTANT(TYPE_DID_FINISH)

    SETCONSTANT(FINISH_STATE_ERROR)
    SETCONSTANT(FINISH_STATE_COMPLETED)
    SETCONSTANT(FINISH_STATE_SKIPPED)

    SETCONSTANT(ERROR_NOT_INITIALIZED)
    SETCONSTANT(ERROR_INITIALIZED_FAILED)
    SETCONSTANT(ERROR_INVALID_ARGUMENT)
    SETCONSTANT(ERROR_VIDEO_PLAYER)
    SETCONSTANT(ERROR_INIT_SANITY_CHECK_FAIL)
    SETCONSTANT(ERROR_AD_BLOCKER_DETECTED)
    SETCONSTANT(ERROR_FILE_IO)
    SETCONSTANT(ERROR_DEVICE_ID)
    SETCONSTANT(ERROR_SHOW)
    SETCONSTANT(ERROR_INTERNAL)

#undef SETCONSTANT
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
	finalize();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUnityAds(dmExtension::Params* params)
{
    //callback_updates();
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static int isSupported(lua_State* L) {
    bool status = false;
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: isSupported() == false");
    lua_pushboolean(L, status);
    return 1;
}

static int Show(lua_State* L) {
	char *placementId_lua = "";
    if (lua_type(L, 1) != LUA_TNONE){
		placementId_lua = (char*)luaL_checkstring(L, 1);
    }
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: Show(\"%s\")", placementId_lua);
    return 0;
}

static int Initialize(lua_State* L) {
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: Initialize()");
    return 0;
}

static int isReady(lua_State* L) {
    bool status = false;
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: isReady() == false");
    lua_pushboolean(L, status);
    return 1;
}

static int isInitialized(lua_State* L) {
    bool status = false;
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: isInitialized() == false");
    lua_pushboolean(L, status);
    return 1;
}

static int getDebugMode(lua_State* L) {
    bool status = true;
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: getDebugMode() == true");
    lua_pushboolean(L, status);
    return 1;
}

static int getVersion(lua_State* L) {
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: getVersion() ==  2.1.1");
    lua_pushstring(L, "2.1.1");
    return 1;
}

static int setDebugMode(lua_State* L) {
    bool status = true;
	dmLogInfo("DefUnityAds[UnsupportedPlatform]: setDebugMode()");
    lua_pushboolean(L, status);
    return 1;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Initialize},
    {"show", Show},
    {"isReady", isReady},
    {"isSupported", isSupported},
    {"isInitialized", isInitialized},
    {"getDebugMode", getDebugMode},
    {"getVersion", getVersion},
    {"setDebugMode", setDebugMode},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}


static dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif // platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeUnityAds, AppFinalizeUnityAds, InitializeUnityAds, UpdateUnityAds, 0, FinalizeUnityAds)
