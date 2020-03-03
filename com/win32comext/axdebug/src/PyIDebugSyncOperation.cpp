// This file implements the IDebugSyncOperation Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIDebugSyncOperation.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIDebugSyncOperation::PyIDebugSyncOperation(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIDebugSyncOperation::~PyIDebugSyncOperation() {}

/* static */ IDebugSyncOperation *PyIDebugSyncOperation::GetI(PyObject *self)
{
    return (IDebugSyncOperation *)PyIUnknown::GetI(self);
}

// @pymethod |PyIDebugSyncOperation|GetTargetThread|Description of GetTargetThread.
PyObject *PyIDebugSyncOperation::GetTargetThread(PyObject *self, PyObject *args)
{
    IDebugSyncOperation *pIDSO = GetI(self);
    if (pIDSO == NULL)
        return NULL;
    IDebugApplicationThread *ppatTarget;
    if (!PyArg_ParseTuple(args, ":GetTargetThread"))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIDSO->GetTargetThread(&ppatTarget);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return OleSetOleError(hr);
    return PyCom_PyObjectFromIUnknown(ppatTarget, IID_IDebugApplicationThread, FALSE);
}

// @pymethod |PyIDebugSyncOperation|Execute|Description of Execute.
PyObject *PyIDebugSyncOperation::Execute(PyObject *self, PyObject *args)
{
    IDebugSyncOperation *pIDSO = GetI(self);
    if (pIDSO == NULL)
        return NULL;
    IUnknown *ppunkResult;
    if (!PyArg_ParseTuple(args, ":Execute"))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIDSO->Execute(&ppunkResult);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return OleSetOleError(hr);
    return PyCom_PyObjectFromIUnknown(ppunkResult, IID_IUnknown, FALSE);
}

// @pymethod |PyIDebugSyncOperation|InProgressAbort|Description of InProgressAbort.
PyObject *PyIDebugSyncOperation::InProgressAbort(PyObject *self, PyObject *args)
{
    IDebugSyncOperation *pIDSO = GetI(self);
    if (pIDSO == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":InProgressAbort"))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIDSO->InProgressAbort();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return OleSetOleError(hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @object PyIDebugSyncOperation|Description of the interface
static struct PyMethodDef PyIDebugSyncOperation_methods[] = {
    {"GetTargetThread", PyIDebugSyncOperation::GetTargetThread,
     1},                                             // @pymeth GetTargetThread|Description of GetTargetThread
    {"Execute", PyIDebugSyncOperation::Execute, 1},  // @pymeth Execute|Description of Execute
    {"InProgressAbort", PyIDebugSyncOperation::InProgressAbort,
     1},  // @pymeth InProgressAbort|Description of InProgressAbort
    {NULL}};

PyComTypeObject PyIDebugSyncOperation::type("PyIDebugSyncOperation", &PyIUnknown::type, sizeof(PyIDebugSyncOperation),
                                            PyIDebugSyncOperation_methods, GET_PYCOM_CTOR(PyIDebugSyncOperation));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGDebugSyncOperation::GetTargetThread(
    /* [out] */ IDebugApplicationThread __RPC_FAR *__RPC_FAR *ppatTarget)
{
    PY_GATEWAY_METHOD;
    if (ppatTarget == NULL)
        return E_POINTER;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetTargetThread", &result);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obppatTarget;
    if (!PyArg_Parse(result, "O", &obppatTarget))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obppatTarget, IID_IDebugApplicationThread, (void **)ppatTarget,
                                               FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGDebugSyncOperation::Execute(
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkResult)
{
    PY_GATEWAY_METHOD;
    if (ppunkResult == NULL)
        return E_POINTER;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Execute", &result);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obppunkResult;
    if (!PyArg_Parse(result, "O", &obppunkResult))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obppunkResult, IID_IUnknown, (void **)ppunkResult, FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGDebugSyncOperation::InProgressAbort(void)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("InProgressAbort", NULL);
    return hr;
}
