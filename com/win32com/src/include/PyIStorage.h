// This file declares the IStorage Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIStorage : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR(PyIStorage);
    static IStorage *GetI(PyObject *self);
    static PyComEnumProviderTypeObject type;

    // The Python methods
    static PyObject *CreateStream(PyObject *self, PyObject *args);
    static PyObject *OpenStream(PyObject *self, PyObject *args);
    static PyObject *CreateStorage(PyObject *self, PyObject *args);
    static PyObject *OpenStorage(PyObject *self, PyObject *args);
    static PyObject *CopyTo(PyObject *self, PyObject *args);
    static PyObject *MoveElementTo(PyObject *self, PyObject *args);
    static PyObject *Commit(PyObject *self, PyObject *args);
    static PyObject *Revert(PyObject *self, PyObject *args);
    static PyObject *EnumElements(PyObject *self, PyObject *args);
    static PyObject *DestroyElement(PyObject *self, PyObject *args);
    static PyObject *RenameElement(PyObject *self, PyObject *args);
    static PyObject *SetElementTimes(PyObject *self, PyObject *args);
    static PyObject *SetClass(PyObject *self, PyObject *args);
    static PyObject *SetStateBits(PyObject *self, PyObject *args);
    static PyObject *Stat(PyObject *self, PyObject *args);

   protected:
    PyIStorage(IUnknown *pdisp);
    ~PyIStorage();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGStorage : public PyGatewayBase, public IStorage {
   protected:
    PyGStorage(PyObject *instance) : PyGatewayBase(instance) { ; }
    PYGATEWAY_MAKE_SUPPORT(PyGStorage, IStorage, IID_IStorage)

    // IStorage
    STDMETHOD(CreateStream)
    (const OLECHAR __RPC_FAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2,
     IStream __RPC_FAR *__RPC_FAR *ppstm);

    STDMETHOD(OpenStream)
    (const OLECHAR __RPC_FAR *pwcsName, void __RPC_FAR *reserved1, DWORD grfMode, DWORD reserved2,
     IStream __RPC_FAR *__RPC_FAR *ppstm);

    STDMETHOD(CreateStorage)
    (const OLECHAR __RPC_FAR *pwcsName, DWORD grfMode, DWORD dwStgFmt, DWORD reserved2,
     IStorage __RPC_FAR *__RPC_FAR *ppstg);

    STDMETHOD(OpenStorage)
    (const OLECHAR __RPC_FAR *pwcsName, IStorage __RPC_FAR *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved,
     IStorage __RPC_FAR *__RPC_FAR *ppstg);

    STDMETHOD(CopyTo)
    (DWORD ciidExclude, const IID __RPC_FAR *rgiidExclude, SNB snbExclude, IStorage __RPC_FAR *pstgDest);

    STDMETHOD(MoveElementTo)
    (const OLECHAR __RPC_FAR *pwcsName, IStorage __RPC_FAR *pstgDest, const OLECHAR __RPC_FAR *pwcsNewName,
     DWORD grfFlags);

    STDMETHOD(Commit)(DWORD grfCommitFlags);

    STDMETHOD(Revert)(void);

    STDMETHOD(EnumElements)
    (DWORD reserved1, void __RPC_FAR *reserved2, DWORD reserved3, IEnumSTATSTG __RPC_FAR *__RPC_FAR *ppenum);

    STDMETHOD(DestroyElement)(const OLECHAR __RPC_FAR *pwcsName);

    STDMETHOD(RenameElement)(const OLECHAR __RPC_FAR *pwcsOldName, const OLECHAR __RPC_FAR *pwcsNewName);

    STDMETHOD(SetElementTimes)
    (const OLECHAR __RPC_FAR *pwcsName, const FILETIME __RPC_FAR *pctime, const FILETIME __RPC_FAR *patime,
     const FILETIME __RPC_FAR *pmtime);

    STDMETHOD(SetClass)(REFCLSID clsid);

    STDMETHOD(SetStateBits)(DWORD grfStateBits, DWORD grfMask);

    STDMETHOD(Stat)(STATSTG __RPC_FAR *pstatstg, DWORD grfStatFlag);
};
