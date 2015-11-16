/**
 * This file is the entry point for Java to communicate with the back end, which is cross platform.
 * It is a wrapper to convert the Java objects into cpp Objects and vice versa.
 */
#include <vector>
#include <string>
#include <jni.h>
#include "watIsLostAPI/headers/graph.h"

using namespace std;

jobjectArray vector2dToJObject(JNIEnv *env, vector< vector<string> > vect){
    jclass stringClass = env->FindClass("java/lang/String");
    jclass objectArrayClass = env->FindClass("[Ljava/lang/String;");

    jsize numNodes = (jsize) vect.size();
    jobjectArray jobj = env->NewObjectArray(numNodes, objectArrayClass, NULL);
    for(int i = 0; i < numNodes; i++){
        int numData = (int) vect[i].size();
        jobjectArray data = env->NewObjectArray(numData, stringClass, NULL);
        for(int j = 0; j < numData; j++){
            env->SetObjectArrayElement(data, j, env->NewStringUTF(vect[i][j].c_str()));
        }
        env->SetObjectArrayElement(jobj, i, data);
    }
    return jobj;
}

extern "C" {

    void Java_com_alstonlin_watislost_MainActivity_loadGraph(JNIEnv *env, jobject thiz, jstring json){
        const char* input = env->GetStringUTFChars(json, NULL);
        Graph::getInstance()->loadGraph(input);
    }

    jintArray Java_com_alstonlin_watislost_MainActivity_findPath(JNIEnv *env, jobject thiz, jint nodeFromId, jint nodeToId){
        vector< int > result = Graph::getInstance()->findPath(nodeFromId, nodeToId);

        jsize numNodes = (jsize) result.size();
        jintArray path = env->NewIntArray(numNodes);
        jint a[numNodes];
        for (int i = 0; i < numNodes; i++){
            a[i] = result[i];
        }
        env->SetIntArrayRegion(path, 0, numNodes, a);
        return path;
    }

    jobjectArray Java_com_alstonlin_watislost_MainActivity_getNodeInfo(JNIEnv *env, jobject thiz){
        vector< vector<string> > result = Graph::getInstance()->getNodeInfo();
        return vector2dToJObject(env, result);
    }

    jobjectArray Java_com_alstonlin_watislost_MainActivity_getMapInfo(JNIEnv *env, jobject thiz){
        vector< vector<string> > result = Graph::getInstance()->getMapInfo();
        return vector2dToJObject(env, result);
    }

    jobjectArray Java_com_alstonlin_watislost_MainActivity_getBuildingInfo(JNIEnv *env, jobject thiz){
        vector< vector<string> > result = Graph::getInstance()->getBuildingInfo();
        return vector2dToJObject(env, result);
    }

}