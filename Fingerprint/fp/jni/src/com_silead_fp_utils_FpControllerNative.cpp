/* DO NOT EDIT THIS FILE - it is machine generated */
#include <assert.h>
#include <android_runtime/AndroidRuntime.h>
#include <jni.h>
#include "JNIHelp.h"
#include "com_silead_fp_utils_FpControllerNative.h"
#include "ainffpsvcclient.h"
#include "ainffpsvcfpapkrelayerCB.h"
#include "utils/Log.h"

#if 0
#include "aremoteapiclient.h"
#include "ainffpsvc.h"
#endif
#include <android/log.h>

#define ADD_CALLBACK_FUNC

//#include <JNIHelp.h>  // For jniRegisterNativeMethods
//#include "sllog.h"
//#include <cutils/log.h>
//import android.util.Log;

//#define error(fmt, ...) ALOGE ("## ERROR : %s(L%d): " fmt "##",__FUNCTION__, __LINE__, ## __VA_ARGS__)
#define LOGE 
#define LOGE_EX 
#define LOG_FATAL_IF(x,y) 

//class AInfFpsvcClient;
//class AInfFpsvcFPApkRelayerCB;
static AInfFpsvcClient* g_Client = NULL;
static AInfFpsvcFPApkRelayerCB* g_Relayer = NULL;
static JavaVM *gJvm;

#ifdef ADD_CALLBACK_FUNC
static jobject mCallbacksObj = NULL;
static jclass  mCallbacksCls = NULL;
static JNIEnv *sCallbackEnv = NULL;
static jmethodID              callbackFuncID;
#endif

static struct {
    jclass clazz;

    jmethodID enrollCredentialRSP;
    jmethodID identifyCredentialRSP;
    jmethodID slfpkeyRSP;
	jmethodID fpGenericCB;
} gFpControllerNativeClassInfo;

static jobject gFpControllerNativeObj;
static JNIEnv *gEnv = NULL;

#if 0
static JNIEnv                 *gJNIEnv;
static jclass                 referClass;
static jmethodID              callbackFuncID;
#endif
void SLFpInfoRSP(SLFpsvcIndex_t info);


static bool checkAndClearExceptionFromCallback(JNIEnv* env, const char* methodName)
{
    if (env->ExceptionCheck()) {
        LOGE("An exception was thrown by callback '%s'.", methodName);
        LOGE_EX(env);
        env->ExceptionClear();
        return true;
    }
    return false;
}
 
jstring c2js(JNIEnv* env, char* src) 
{  
    jclass strClass = env->FindClass("java/lang/String");   
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V"); 
    jbyteArray bytes = env->NewByteArray(strlen(src));  
    env->SetByteArrayRegion(bytes, 0, strlen(src), (jbyte*)src);    
    jstring encoding = env->NewStringUTF("utf-8");  
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);  
}

jobject getInstance(JNIEnv* env, jclass srcClass)
{
    jmethodID construction_id = env->GetMethodID(srcClass, "<init>", "()V");
    jobject obj = env->NewObject(srcClass, construction_id);
    return obj;
}

void fpGenericCB(int index, char* event_name, int result, char* event_data)
{
    if (gFpControllerNativeObj) {
        JNIEnv* env = gEnv;
		jstring evt_name = c2js(env, event_name);
		jstring evt_data = c2js(env, event_data);
        env->CallVoidMethod(gFpControllerNativeObj, gFpControllerNativeClassInfo.fpGenericCB,
                index, evt_name, result, evt_data);
        checkAndClearExceptionFromCallback(env, "fpGenericCB");
    }
}

void slfpkeyRSP (int fpkeyret) {
    if (gFpControllerNativeObj) {
       JNIEnv* env;
       if (gJvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
            return;
       }
        env->CallVoidMethod(gFpControllerNativeObj, gFpControllerNativeClassInfo.slfpkeyRSP,
        		fpkeyret);
       checkAndClearExceptionFromCallback(env, "slfpkeyRSP");
       gJvm->DetachCurrentThread();
    }
}

void enrollCredentialRSP (int index, int percent, int result, int area) {
    if (gFpControllerNativeObj) {
       JNIEnv* env;
//__android_log_print(4, "[SL_FP]", "enrollCredentialRSP before CallVoidMethod env 222 = %p",env);
       if (gJvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
//           __android_log_print(4, "[SL_FP]", "enrollCredentialRSP Attach error ");
            return;
       }
 //__android_log_print(4, "[SL_FP]", "enrollCredentialRSP before CallVoidMethod gEnv = %p",gEnv);
        env->CallVoidMethod(gFpControllerNativeObj, gFpControllerNativeClassInfo.enrollCredentialRSP,
                 index, percent, result, area);
//__android_log_print(4, "[SL_FP]", "enrollCredentialRSP after CallVoidMethod");
       checkAndClearExceptionFromCallback(env, "enrollCredentialRSP");
       gJvm->DetachCurrentThread();
    }
}

void identifyCredentialRSP (int index, int result,int fingerid) {
    if (gFpControllerNativeObj) {
		JNIEnv* env;
		if (gJvm->AttachCurrentThread(&env, NULL) != JNI_OK) {return;}
//		__android_log_print(4, "[SL_FP]", "identifyCredentialRSP before CallVoidMethod $$$ \n");
        env->CallVoidMethod(gFpControllerNativeObj, gFpControllerNativeClassInfo.identifyCredentialRSP,
                index, result,fingerid);
//		__android_log_print(4, "[SL_FP]", "identifyCredentialRSP after CallVoidMethod $$$ \n");
        checkAndClearExceptionFromCallback(env, "identifyCredentialRSP");
        gJvm->DetachCurrentThread();
    }

}

static jobject com_silead_fp_utils_FpControllerNative_nativeGetFpInfo(
	JNIEnv		*env,
	jobject		object
	){

	__android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeGetFpInfo enter");
	SLFpsvcIndex_t info;
	g_Client->GetFPInfo(&info);
	__android_log_print(4, "[SL_FP]", "info total=%d max=%d wenable=%d frame_w=%d frame_h=%d",info.total,info.max,info.wenable,info.frame_w,info.frame_h);
    for(int i=0; i < SL_SLOT_ALL; i++)
    {
    	__android_log_print(4, "[SL_FP]", "info.fpinfo index=%d slot=%d enable=%d fingername = %s i=%d",info.fpinfo[i].index,info.fpinfo[i].slot,info.fpinfo[i].enable,info.fpinfo[i].fingername,i);
    }

	jclass  j_infoclazz = env->FindClass("com/silead/fp/utils/FpControllerNative$SLFpsvcFPInfo");
    jfieldID jindex = env->GetFieldID(j_infoclazz, "enrollIndex", "I");
    jfieldID jslot = env->GetFieldID(j_infoclazz, "slot", "I");
    jfieldID jenable = env->GetFieldID(j_infoclazz, "enable", "I");
    jfieldID jfingername = env->GetFieldID(j_infoclazz, "fingerName", "Ljava/lang/String;");

    __android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeGetFpInfo SLFpsvcFPInfo = %d",j_infoclazz);

    jclass  clazzz = env->FindClass("com/silead/fp/utils/FpControllerNative$SLFpsvcIndex");

    __android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeGetFpInfo SLFpsvcIndex = %d",clazzz);
    jfieldID jtotal = env->GetFieldID(clazzz, "total", "I");
    jfieldID jmax = env->GetFieldID(clazzz, "max", "I");
    jfieldID jwenable = env->GetFieldID(clazzz, "wenable", "I");
    jfieldID jframe_w = env->GetFieldID(clazzz, "frame_w", "I");
    jfieldID jframe_h = env->GetFieldID(clazzz, "frame_h", "I");
    jfieldID jffpinfo = env->GetFieldID(clazzz, "FPInfo", "[Lcom/silead/fp/utils/FpControllerNative$SLFpsvcFPInfo;");

    jobjectArray joRecArr = env->NewObjectArray(SL_SLOT_ALL,j_infoclazz,0);
    for(int i=0; i < SL_SLOT_ALL; i++){
		jobject temp = env->AllocObject(j_infoclazz);
		env->SetIntField(temp, jindex, info.fpinfo[i].index);
		env->SetIntField(temp, jslot, info.fpinfo[i].slot);
		env->SetIntField(temp, jenable, info.fpinfo[i].enable);
		jstring jstrTmp = env->NewStringUTF(info.fpinfo[i].fingername);
		env->SetObjectField(temp, jfingername, jstrTmp);
		env->SetObjectArrayElement(joRecArr, i, temp);
		}
    jobject obj = env->AllocObject(clazzz);
    env->SetIntField(obj, jtotal, info.total);
    env->SetIntField(obj, jmax, info.max);
    env->SetIntField(obj, jwenable, info.wenable);
    env->SetIntField(obj, jframe_w, info.frame_w);
    env->SetIntField(obj, jframe_h, info.frame_h);
    env->SetObjectField(obj, jffpinfo, joRecArr);

    return obj;

}

static jint com_silead_fp_utils_FpControllerNative_nativeSetfpInfo(
		JNIEnv		*env,
		jobject		object,
		jobject		fpindex
		){
	__android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeSetfpInfo enter");
	SLFpsvcIndex_t info;
	jclass  clazzz = env->FindClass("com/silead/fp/utils/FpControllerNative$SLFpsvcIndex");
	jfieldID jtotal = env->GetFieldID(clazzz, "total", "I");
    jfieldID jmax = env->GetFieldID(clazzz, "max", "I");
    jfieldID jwenable = env->GetFieldID(clazzz, "wenable", "I");
    jfieldID jframe_w = env->GetFieldID(clazzz, "frame_w", "I");
    jfieldID jframe_h = env->GetFieldID(clazzz, "frame_h", "I");
    jfieldID jffpinfo = env->GetFieldID(clazzz, "FPInfo", "[Lcom/silead/fp/utils/FpControllerNative$SLFpsvcFPInfo;");

    jclass  j_infoclazz = env->FindClass("com/silead/fp/utils/FpControllerNative$SLFpsvcFPInfo");
    jfieldID jindex = env->GetFieldID(j_infoclazz, "enrollIndex", "I");
    jfieldID jslot = env->GetFieldID(j_infoclazz, "slot", "I");
    jfieldID jenable = env->GetFieldID(j_infoclazz, "enable", "I");
    jfieldID jfingername = env->GetFieldID(j_infoclazz, "fingerName", "Ljava/lang/String;");

    info.total = env->GetIntField(fpindex, jtotal );
    info.max = env->GetIntField(fpindex, jmax );
    info.wenable = env->GetIntField(fpindex, jwenable );
    info.frame_w = env->GetIntField(fpindex, jframe_w);
    info.frame_h = env->GetIntField(fpindex, jframe_h);
    jobjectArray joRecArr = (jobjectArray)env->GetObjectField(fpindex,jffpinfo);

    for(int i=0; i < SL_SLOT_ALL; i++){
		jobject temp = env->GetObjectArrayElement(joRecArr, i);
		info.fpinfo[i].index = env->GetIntField(temp, jindex);
		info.fpinfo[i].slot = env->GetIntField(temp, jslot);
		info.fpinfo[i].enable = env->GetIntField(temp, jenable);
		jstring jstrTmp = (jstring)env->GetObjectField(temp, jfingername);
		int lengthtmp = env->GetStringUTFLength(jstrTmp);
		const char* tmp = env->GetStringUTFChars(jstrTmp, 0);
		strncpy(info.fpinfo[i].fingername,tmp,FINGERNAMELEN*2);
		info.fpinfo[i].fingername[FINGERNAMELEN*2] = '\0';
		}


    __android_log_print(4, "[SL_FP]", "info total=%d max=%d wenable=%d frame_w=%d frame_h=%d",info.total,info.max,info.wenable,info.frame_w,info.frame_h);
    for(int i=0; i < SL_SLOT_ALL; i++)
    {
    	__android_log_print(4, "[SL_FP]", "info.fpinfo index=%d slot=%d enable=%d fingername = %s i=%d",info.fpinfo[i].index,info.fpinfo[i].slot,info.fpinfo[i].enable,info.fpinfo[i].fingername,i);
    }
	int ret =  g_Client->SetFPInfo(&info);
	__android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeSetfpInfo ret = %d",ret);
	return ret;
}

static void com_silead_fp_utils_FpControllerNative_nativeInit(
	JNIEnv		*env,
	jobject		object
	) {
    if (env->GetJavaVM(&gJvm) < 0) {
        LOGE("com_silead_fp_utils_FpControllerNative_nativeInit Could not get handle to the VM");
    }
    __android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeInit $$$ env = %p , gJvm = %p \n",env,gJvm);
    gFpControllerNativeObj = env->NewGlobalRef(object);

}


static jint com_silead_fp_utils_FpControllerNative_nativeInitFPSystem(
	JNIEnv		*env,
	jobject		object
	) {
	__android_log_print(4, "[SL_FP]", "com_silead_fp_utils_FpControllerNative_nativeInitFPSystem $$$ enter \n");
	if(!g_Relayer)
	{
		g_Relayer = AInfFpsvcFPApkRelayerCB::Create();
		assert(g_Relayer);
	}
	if(!g_Client)
	{
		g_Client = AInfFpsvcClient::Create(g_Relayer);
		assert(g_Client);
	}
	return 1;
}

/*
 * Class:     com_android_silead_FpControllerNative
 * Method:    EnrollCredentialREQ
 * Signature: ()V
 */
static jint com_silead_fp_utils_FpControllerNative_nativeEnrollCredentialREQ(
	JNIEnv		*env,
	jobject		object,
	jint index
	) {
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeEnrollCredentialREQ");
	return g_Client->EnrollCredential(index);
}

/*
 * Class:     com_android_silead_FpControllerNative
 * Method:    IdentifyCredentialREQ
 * Signature: ()V
 */
static jint com_silead_fp_utils_FpControllerNative_nativeIdentifyCredentialREQ(
	JNIEnv		*env, 
	jobject		object,
	jint index
	) {
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeIdentifyCredentialREQ _debug");
	return g_Client->IdentifyCredential(index);
}

/*
 * Class:     com_android_silead_FpControllerNative
 * Method:    RemoveCredential
 * Signature: (I)I
 */
static jint com_silead_fp_utils_FpControllerNative_nativeRemoveCredential(
	JNIEnv		*env, 
	jobject		object, 
	jint		index
	) {
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeRemoveCredential");
	return g_Client->RemoveCredential(index);
}


/*
 * Class:     com_android_silead_FpControllerNative
 * Method:    DestoryFPSystem
 * Signature: ()I
 */
static jint com_silead_fp_utils_FpControllerNative_nativeDestoryFPSystem(
	JNIEnv		*env, 
	jobject		object
	) {
//	if(g_Client)
//	{
//		delete g_Client;
//		g_Client = NULL;
//	}

	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeDestoryFPSystem");
	return 1;
}

static jint com_silead_fp_utils_FpControllerNative_nativeResetFPService(
	JNIEnv		*env,
	jobject		object
	){
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeResetFPService");
	return g_Client->ResetFPService();
}

static jint com_silead_fp_utils_FpControllerNative_nativeEnalbeCredential(
	JNIEnv		*env,
	jobject		object,
	jint		index,
	jint		enable
	){
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeEnalbeCredential");
	return g_Client->EnalbeCredential(index,enable);
}

static jint com_silead_fp_utils_FpControllerNative_nativeGetEnableCredential(
	JNIEnv		*env,
	jobject		object,
	jint		index
	){
	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeFpCancelOperation ");
	return g_Client->GetEnableCredential(index);
}
static jint com_silead_fp_utils_FpControllerNative_nativeFpCancelOperation(
	JNIEnv		*env,
	jobject		object
	){

	__android_log_print(4, "[SL_FP]","com_silead_fp_utils_FpControllerNative_nativeFpCancelOperation _debug");
	return g_Client->FpCancelOperation();
}


static JNINativeMethod gMethods[] = {
  {"nativeInit",                        "()V",          (void *)com_silead_fp_utils_FpControllerNative_nativeInit},
  {"nativeInitFPSystem",                "()I",          (void *)com_silead_fp_utils_FpControllerNative_nativeInitFPSystem},
  {"nativeDestoryFPSystem",             "()I",          (void *)com_silead_fp_utils_FpControllerNative_nativeDestoryFPSystem},
  {"nativeEnrollCredentialREQ",         "(I)I",         (void *)com_silead_fp_utils_FpControllerNative_nativeEnrollCredentialREQ},
  {"nativeIdentifyCredentialREQ",       "(I)I",         (void *)com_silead_fp_utils_FpControllerNative_nativeIdentifyCredentialREQ},
  {"nativeResetFPService",            	"()I",         	(void *)com_silead_fp_utils_FpControllerNative_nativeResetFPService},
  {"nativeRemoveCredential",            "(I)I",         (void *)com_silead_fp_utils_FpControllerNative_nativeRemoveCredential},
  {"nativeEnalbeCredential",            "(II)I",        (void *)com_silead_fp_utils_FpControllerNative_nativeEnalbeCredential},
  {"nativeGetEnableCredential",        	"(I)I",         (void *)com_silead_fp_utils_FpControllerNative_nativeGetEnableCredential},
  {"nativeFpCancelOperation",         	"()I",         	(void *)com_silead_fp_utils_FpControllerNative_nativeFpCancelOperation},
  {"nativeGetFpInfo",         			"()Lcom/silead/fp/utils/FpControllerNative$SLFpsvcIndex;",         	(void *)com_silead_fp_utils_FpControllerNative_nativeGetFpInfo},
  {"nativeSetFpInfo",         			"(Lcom/silead/fp/utils/FpControllerNative$SLFpsvcIndex;)I",         	(void *)com_silead_fp_utils_FpControllerNative_nativeSetfpInfo},
};

#define FIND_CLASS(var, className) \
	{ \
		var = env->FindClass(className); \
		LOG_FATAL_IF(! var, "Unable to find class " className); \
		var = jclass(env->NewGlobalRef(var)); \
	}

#define GET_METHOD_ID(var, clazz, methodName, methodDescriptor) \
        var = env->GetMethodID(clazz, methodName, methodDescriptor); \
        LOG_FATAL_IF(! var, "Unable to find method " methodName);

#define GET_FIELD_ID(var, clazz, fieldName, fieldDescriptor) \
        var = env->GetFieldID(clazz, fieldName, fieldDescriptor); \
        LOG_FATAL_IF(! var, "Unable to find field " fieldName);

int register_com_silead_fp_utils_FpControllerNative(JNIEnv* env,
	const char* className,
	const JNINativeMethod* jniMethods,
	int numMethods) {
    int res = jniRegisterNativeMethods(env, className, jniMethods, numMethods);
	gEnv = env;
    LOG_FATAL_IF(res < 0, " register_com_silead_fp_utils_FpControllerNative Unable to register native methods.");
	__android_log_print(4, "[SL_FP]", "[wq]:jniRegisterNativeMethods:start numMethods = %d,env = %p\n",numMethods,env);
    FIND_CLASS(gFpControllerNativeClassInfo.clazz, className);
    if (gFpControllerNativeClassInfo.clazz == NULL) {
      //  __android_log_print(ANDROID_LOG_ERROR, TAG, "Native registration unable to find class '%s'\n", className);
		__android_log_print(4, "[SL_FP]", "[wq]:jniRegisterNativeMethods:0\n");
	    return -1;
    }

    GET_METHOD_ID(gFpControllerNativeClassInfo.enrollCredentialRSP, gFpControllerNativeClassInfo.clazz,
            "enrollCredentialRSP", "(IIII)V");
    GET_METHOD_ID(gFpControllerNativeClassInfo.slfpkeyRSP, gFpControllerNativeClassInfo.clazz,
                "slfpkeyRSP", "(I)V");
    GET_METHOD_ID(gFpControllerNativeClassInfo.identifyCredentialRSP, gFpControllerNativeClassInfo.clazz,
            "identifyCredentialRSP", "(III)V");
    GET_METHOD_ID(gFpControllerNativeClassInfo.fpGenericCB, gFpControllerNativeClassInfo.clazz,
            "fpGenericCB", "(ILjava/lang/String;ILjava/lang/String;)V");
   __android_log_print(4, "[SL_FP]", "[wq]:jniRegisterNativeMethods:1 numMethods = %d\n",numMethods);

    return 0;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env = NULL;
	int ret = -1;
	__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:start\n");

	if (vm->GetEnv((void **)&env, JNI_VERSION_1_4) != JNI_OK) {
		__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:0\n");
		return -1;
	}
	__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:1 env = %p\n",env);
	assert(env != NULL);
	__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:2\n");
	ret = register_com_silead_fp_utils_FpControllerNative(env, "com/silead/fp/utils/FpControllerNative", gMethods, sizeof(gMethods)/sizeof(gMethods[0]));
	if ( ret < 0 ) {
		__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:3\n");
		return -1;
	}
		__android_log_print(4, "[SL_FP]", "[wq]:JNI_OnLoad:end\n");
	return JNI_VERSION_1_4;
}


