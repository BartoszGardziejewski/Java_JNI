#include <iostream>
#include <numeric>
#include "DotProduct.h"

using namespace std;

JNIEXPORT jdouble JNICALL Java_DotProduct_CalculateDotProduct1(JNIEnv *env, jobject thisObj, jobjectArray x, jobjectArray y)
{

	jobject vecX = env->GetObjectArrayElement(x, 0);
	jobject vecY = env->GetObjectArrayElement(y, 0);

	jclass DoubleClass = env->GetObjectClass(vecX);
	jfieldID fidDouble = env->GetFieldID(DoubleClass, "value", "D");

	jdouble length = env->GetArrayLength(x);

	double z=0;

	for (int i = 0; i<length; i++)
	{
		vecX = env->GetObjectArrayElement(x, i);
		vecY = env->GetObjectArrayElement(y, i);

		jdouble xFalue = env->GetDoubleField(vecX, fidDouble);
		jdouble yFalue = env->GetDoubleField(vecY, fidDouble);

		z += xFalue * yFalue;
	}


	return (jdouble)z;
}

JNIEXPORT jdouble JNICALL Java_DotProduct_CalculateDotProduct2(JNIEnv *env, jobject thisObj, jobjectArray x) 
{	

	jobject vecX = env->GetObjectArrayElement(x, 0);
	jobject vecY;

	jclass DoubleClass = env->GetObjectClass(vecX);
	jclass ThisClass = env->GetObjectClass(thisObj);

	jfieldID YDouble = env->GetFieldID(ThisClass, "y", "[Ljava/lang/Double;");
	jfieldID fidDouble = env->GetFieldID(DoubleClass, "value", "D");

	jobjectArray y = (jobjectArray)env->GetObjectField(thisObj, YDouble);
	jdouble length = env->GetArrayLength(x);

	double z = 0;

	for (int i = 0; i<length; i++)
	{
		vecX = env->GetObjectArrayElement(x, i);
		vecY = env->GetObjectArrayElement(y, i);

		jdouble xFalue = env->GetDoubleField(vecX, fidDouble);
		jdouble yFalue = env->GetDoubleField(vecY, fidDouble);

		z += xFalue * yFalue;
	}


	return (jdouble)z;
}


JNIEXPORT void JNICALL Java_DotProduct_CalculateDotProduct3(JNIEnv *env, jobject thisObj) 
{
	int size=0;
	cout << "size of vectors:" << endl;
	cin >> size;

	double* tmpX = new double[size];
	double* tmpY = new double[size];

	jclass DoubleClass = env->FindClass("Ljava/lang/Double;");
	jmethodID constructor = env->GetMethodID(DoubleClass, "<init>", "(D)V");

	if (size <= 0) {
		return;
	}

	jobject x1 = env->NewObject(DoubleClass, constructor, 0);
	jobject y1 = env->NewObject(DoubleClass, constructor, 0);
	jobjectArray xA = env->NewObjectArray(size, DoubleClass, x1);
	jobjectArray yA = env->NewObjectArray(size, DoubleClass, y1);

	cout << "X vector values:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "x" << i << ":  ";
		cin >> tmpX[i];
		x1 = env->NewObject(DoubleClass, constructor, tmpX[i]);
		env->SetObjectArrayElement(xA, i, x1);
		cout << endl;
	}

	cout << "Y vector values:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "y" << i << ":  ";
		cin >> tmpY[i];
		y1 = env->NewObject(DoubleClass, constructor, tmpY[i]);
		env->SetObjectArrayElement(yA, i, y1);
		cout << endl;
	}


	jclass ThisClass = env->GetObjectClass(thisObj);

	jmethodID setX = env->GetMethodID(ThisClass, "setX", "([Ljava/lang/Double;)V");
	jmethodID setY = env->GetMethodID(ThisClass, "setY", "([Ljava/lang/Double;)V");
	jmethodID calcID = env->GetMethodID(ThisClass, "CalculateInnerDotProduct", "()V");

	env->CallVoidMethod(thisObj, setX, xA);
	env->CallVoidMethod(thisObj, setY, yA);
	env->CallVoidMethod(thisObj, calcID);

	delete[] tmpX;
	delete[] tmpY;

	return;
}