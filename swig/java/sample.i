%module LibraryT

%{
#include <libraryT/utiles.h>
#include <libraryT/capi.h>
%}

// -------------------- 对std::vector的支持 --------------------
%include std_vector.i
%template(IntVector) std::vector<int>;

// -------------------- 对C数组的支持 --------------------
// 方法一
// %include carrays.i
// %array_functions(int, IntArray);
// 方法二
%include arrays_java.i
%typemap(jni) (int *arr, int size) "jintArray";
%typemap(jtype) (int *arr, int size) "int[]";
%typemap(jstype) (int *arr, int size) "int[]";
%typemap(javain) (int *arr, int size) "$javainput";
%typemap(in) (int *arr, int size) {
    $1 = (int *) JCALL2(GetIntArrayElements, jenv, $input, NULL);
    $2 = JCALL1(GetArrayLength, jenv, $input);
};
%typemap(freearg) (int *arr, int size) {
    JCALL3(ReleaseIntArrayElements, jenv, $input, (jint*)$1, 0);
}

// -------------------- 对size_t的支持 --------------------
%apply unsigned long long { size_t };

// -------------------- 对回调函数的支持 --------------------
%header %{
typedef struct {
    JNIEnv *jenv;
    jobject pJavaCallback;
} JavaProgressData;
%}

%inline %{
class JvPrintCallback {
public:
    virtual ~JvPrintCallback() { }
    virtual int run(const char *) {
        printf("JvPrintCallback is running ...\n");
        return 1;
    }
};
%}

%{
static int JavaProgressProxy(const char *pszMessage, void *pData) {
    JavaProgressData *psProgressInfo = (JavaProgressData *)pData;
    JNIEnv *jenv = psProgressInfo->jenv;
    int ret;
    const jclass printCallbackClass = jenv->FindClass("libraryT/scripts/JvPrintCallback");
    if (printCallbackClass == nullptr) {
        printf("Can't find Callback Class in \"libraryT/scripts/JvPrintCallback\".\n");
    }
    const jmethodID runMethod = jenv->GetMethodID(printCallbackClass, "run", "(Ljava/lang/String;)I");
    jstring temp_string = jenv->NewStringUTF(pszMessage);
    ret = jenv->CallIntMethod(psProgressInfo->pJavaCallback, runMethod, temp_string);
    jenv->DeleteLocalRef(temp_string);
    return ret;
}
%}

// 注意对%typemap和%extend等来说，如果有命名空间的话，需要加上命名空间
%typemap(arginit, noblock=1) (libraryT::utiles::PrintCallback callback, void *data) {
    JavaProgressData sProgressInfo;
    sProgressInfo.jenv = jenv;
    sProgressInfo.pJavaCallback = NULL;
}

%typemap(in) (libraryT::utiles::PrintCallback callback, void *data) {
    if ($input != 0) {
        sProgressInfo.pJavaCallback = $input;
        $1 = JavaProgressProxy;
        $2 = &sProgressInfo;
    } else {
        $1 = NULL;
        $2 = NULL;
    }
}

%typemap(jni) (libraryT::utiles::PrintCallback callback, void *data) "jobject"
%typemap(jtype) (libraryT::utiles::PrintCallback callback, void *data) "JvPrintCallback"
%typemap(jstype) (libraryT::utiles::PrintCallback callback, void *data) "JvPrintCallback"
%typemap(javain) (libraryT::utiles::PrintCallback callback, void *data) "$javainput"
%typemap(javaout) (libraryT::utiles::PrintCallback callback, void *data) { return $jnicall; }

// -------------------- 导入需要解析的代码 --------------------
%include <libraryT/utiles.h>
%include <libraryT/capi.h>

// -------------------- 新增方法 --------------------
%extend libraryT::utiles::Point {
    static libraryT::utiles::Point create(double x, double y) {
        return libraryT::utiles::Point{x, y};
    }
};