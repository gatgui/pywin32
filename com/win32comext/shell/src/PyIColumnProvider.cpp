// This file implements the IColumnProvider Interface and Gateway for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyIColumnProvider.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIColumnProvider::PyIColumnProvider(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIColumnProvider::~PyIColumnProvider() {}

/* static */ IColumnProvider *PyIColumnProvider::GetI(PyObject *self)
{
    return (IColumnProvider *)PyIUnknown::GetI(self);
}

// @pymethod |PyIColumnProvider|Initialize|Description of Initialize.
PyObject *PyIColumnProvider::Initialize(PyObject *self, PyObject *args)
{
    IColumnProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    SHCOLUMNINIT psci;
    PyObject *obpsci;
    // @pyparm <o PyCSHCOLUMNINIT>|psci||Description for psci
    if (!PyArg_ParseTuple(args, "O:Initialize", &obpsci))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsSHCOLUMNINIT(obpsci, &psci))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICP->Initialize(&psci);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_IColumnProvider);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIColumnProvider|GetColumnInfo|Description of GetColumnInfo.
PyObject *PyIColumnProvider::GetColumnInfo(PyObject *self, PyObject *args)
{
    IColumnProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    // @pyparm int|dwIndex||Description for dwIndex
    DWORD dwIndex;
    if (!PyArg_ParseTuple(args, "l:GetColumnInfo", &dwIndex))
        return NULL;
    HRESULT hr;
    SHCOLUMNINFO psci;
    PY_INTERFACE_PRECALL;
    hr = pICP->GetColumnInfo(dwIndex, &psci);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_IColumnProvider);
    if (hr == S_FALSE) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return PyObject_FromSHCOLUMNINFO(&psci);
}

// @pymethod |PyIColumnProvider|GetItemData|Description of GetItemData.
PyObject *PyIColumnProvider::GetItemData(PyObject *self, PyObject *args)
{
    IColumnProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    SHCOLUMNID pscid;
    PyObject *obpscid;
    // @pyparm <o PySHCOLUMNID>|pscid||Description for pscid
    SHCOLUMNDATA pscd;
    PyObject *obpscd;
    // @pyparm <o PySHCOLUMNDATA>|pscd||Description for pscd
    VARIANT varData;
    VariantInit(&varData);
    if (!PyArg_ParseTuple(args, "OO:GetItemData", &obpscid, &obpscd))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsSHCOLUMNID(obpscid, &pscid))
        bPythonIsHappy = FALSE;
    if (bPythonIsHappy && !PyObject_AsSHCOLUMNDATA(obpscd, &pscd))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICP->GetItemData(&pscid, &pscd, &varData);
    PY_INTERFACE_POSTCALL;
    PyObject_FreeSHCOLUMNDATA(&pscd);
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_IColumnProvider);
    PyObject *obRet = PyCom_PyObjectFromVariant(&varData);
    VariantClear(&varData);
    return obRet;
}

// @object PyIColumnProvider|Description of the interface
static struct PyMethodDef PyIColumnProvider_methods[] = {
    {"Initialize", PyIColumnProvider::Initialize, 1},        // @pymeth Initialize|Description of Initialize
    {"GetColumnInfo", PyIColumnProvider::GetColumnInfo, 1},  // @pymeth GetColumnInfo|Description of GetColumnInfo
    {"GetItemData", PyIColumnProvider::GetItemData, 1},      // @pymeth GetItemData|Description of GetItemData
    {NULL}};

PyComTypeObject PyIColumnProvider::type("PyIColumnProvider", &PyIUnknown::type, sizeof(PyIColumnProvider),
                                        PyIColumnProvider_methods, GET_PYCOM_CTOR(PyIColumnProvider));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGColumnProvider::Initialize(
    /* [unique][in] */ LPCSHCOLUMNINIT psci)
{
    PY_GATEWAY_METHOD;
    PyObject *obpsci = PyObject_FromSHCOLUMNINIT(psci);
    if (obpsci == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("Initialize");
    HRESULT hr = InvokeViaPolicy("Initialize", NULL, "(O)", obpsci);
    Py_DECREF(obpsci);
    return hr;
}

STDMETHODIMP PyGColumnProvider::GetColumnInfo(
    /* [unique][in] */ DWORD dwIndex,
    /* [out] */ LPSHCOLUMNINFO psci)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetColumnInfo", &result, "l", dwIndex);
    if (FAILED(hr))
        return hr;
    if (result == Py_None)
        hr = S_FALSE;
    else {
        PyObject_AsSHCOLUMNINFO(result, psci);
        hr = PyCom_SetCOMErrorFromPyException(GetIID());
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGColumnProvider::GetItemData(
    /* [unique][in] */ LPCSHCOLUMNID pscid,
    /* [unique][in] */ LPCSHCOLUMNDATA pscd,
    /* [unique][out] */ VARIANT *pvarData)
{
    PY_GATEWAY_METHOD;
    PyObject *obpscid = PyObject_FromSHCOLUMNID(pscid);
    if (obpscid == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetItemData");
    PyObject *obpscd = PyObject_FromSHCOLUMNDATA(pscd);
    if (obpscd == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetItemData");
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetItemData", &result, "OO", obpscid, obpscd);
    Py_DECREF(obpscid);
    Py_DECREF(obpscd);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    if (result == Py_None)
        hr = S_FALSE;
    else {
        PyCom_VariantFromPyObject(result, pvarData);
        hr = PyCom_SetCOMErrorFromPyException(GetIID());
    }
    Py_DECREF(result);
    return hr;
}
