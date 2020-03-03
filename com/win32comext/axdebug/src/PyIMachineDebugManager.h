// This file declares the IMachineDebugManager Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIMachineDebugManager : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR_ERRORINFO(PyIMachineDebugManager, IID_IMachineDebugManager);
    static IMachineDebugManager *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *AddApplication(PyObject *self, PyObject *args);
    static PyObject *RemoveApplication(PyObject *self, PyObject *args);
    static PyObject *EnumApplications(PyObject *self, PyObject *args);

   protected:
    PyIMachineDebugManager(IUnknown *pdisp);
    ~PyIMachineDebugManager();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGMachineDebugManager : public PyGatewayBase, public IMachineDebugManager {
   protected:
    PyGMachineDebugManager(PyObject *instance) : PyGatewayBase(instance) { ; }
    PYGATEWAY_MAKE_SUPPORT(PyGMachineDebugManager, IMachineDebugManager, IID_IMachineDebugManager)

    // IMachineDebugManager
    STDMETHOD(AddApplication)(IRemoteDebugApplication __RPC_FAR *pda, DWORD __RPC_FAR *pdwAppCookie);

    STDMETHOD(RemoveApplication)(DWORD dwAppCookie);

    STDMETHOD(EnumApplications)(IEnumRemoteDebugApplications __RPC_FAR *__RPC_FAR *ppeda);
};
