// This file implements the IInternetPriority Interface and Gateway for Python.
// Generated by makegw.py

#include "internet_pch.h"
#include "PyIInternetPriority.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIInternetPriority::PyIInternetPriority(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIInternetPriority::~PyIInternetPriority() {}

/* static */ IInternetPriority *PyIInternetPriority::GetI(PyObject *self)
{
    return (IInternetPriority *)PyIUnknown::GetI(self);
}

// @pymethod |PyIInternetPriority|SetPriority|Description of SetPriority.
PyObject *PyIInternetPriority::SetPriority(PyObject *self, PyObject *args)
{
    IInternetPriority *pIIP = GetI(self);
    if (pIIP == NULL)
        return NULL;
    // @pyparm int|nPriority||Description for nPriority
    LONG nPriority;
    if (!PyArg_ParseTuple(args, "i:SetPriority", &nPriority))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIIP->SetPriority(nPriority);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIInternetPriority|GetPriority|Description of GetPriority.
PyObject *PyIInternetPriority::GetPriority(PyObject *self, PyObject *args)
{
    IInternetPriority *pIIP = GetI(self);
    if (pIIP == NULL)
        return NULL;
    LONG pnPriority;
    if (!PyArg_ParseTuple(args, ":GetPriority"))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIIP->GetPriority(&pnPriority);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);

    PyObject *pyretval = Py_BuildValue("i", pnPriority);
    return pyretval;
}

// @object PyIInternetPriority|Description of the interface
static struct PyMethodDef PyIInternetPriority_methods[] = {
    {"SetPriority", PyIInternetPriority::SetPriority, 1},  // @pymeth SetPriority|Description of SetPriority
    {"GetPriority", PyIInternetPriority::GetPriority, 1},  // @pymeth GetPriority|Description of GetPriority
    {NULL}};

PyComTypeObject PyIInternetPriority::type("PyIInternetPriority", &PyIUnknown::type, sizeof(PyIInternetPriority),
                                          PyIInternetPriority_methods, GET_PYCOM_CTOR(PyIInternetPriority));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGInternetPriority::SetPriority(
    /* [in] */ LONG nPriority)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("SetPriority", NULL, "i", nPriority);
    return hr;
}

STDMETHODIMP PyGInternetPriority::GetPriority(
    /* [out] */ LONG __RPC_FAR *pnPriority)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetPriority", &result);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    if (!PyArg_Parse(result, "i", pnPriority))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}
