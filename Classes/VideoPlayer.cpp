#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "cocos2d.h"
#include "VideoPlayer.h"
#include <jni.h>
#include "jni/JniHelper.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

bool VideoPlayer::init()
{
    return true;
}

void VideoPlayer::play(const char* path, const char* type)
{
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                      "jp/co/befool/VideoPlayer",
                                      "play",
                                      "(Ljava/lang/String;)V")) {
        jstring StringArg1 = minfo.env->NewStringUTF(cocos2d::StringUtils::format("%s.%s", path, type).c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
}
#endif
