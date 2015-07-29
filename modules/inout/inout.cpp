#include "inout.h"
#include "widget.h" // ! Нельзя включать в хидере
#include "sender.h"

InputOutput *inputoutput = new InputOutput();

char* argv[] = {"./Kate",""};
int argc = 1;

QApplication MainApp(argc,argv); // глобальные в lib.h
Widget w(0);


void inout::start_main(){

    inputoutput->printLogFile("create QApplication \n");
    w.show();
    inputoutput->printLogFile("show widget \n");

    MainApp.exec();
    inputoutput->printLogFile("exec \n");
    
    
};



void inout::start(){

//    inputoutput->printLogFile("create QApplication \n");
//    w.show();
//    inputoutput->printLogFile("show widget \n");
//
//    MainApp.exec();
//    inputoutput->printLogFile("exec \n");
    
    sender sendarman;
    sendarman.addconnect(w);
    for (int i = 0; i < 300; ++i)
    {
        std::string str = "::INOUT  ";
        inputoutput->printLogFile(str + std::to_string(i) +  "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        sendarman.sendtic();
    }
    
};


InputOutput::InputOutput(){
    name = "inout";
    logFileName = ".Input_Output_log";
    openLogFile();
};

InputOutput::~InputOutput(){
    name = "NULL";
};


void InputOutput::update(){

//    message* tic_msg = 0;
//    std::clock_t* _tic = 0;
    inputoutput->printLogFile("get tic \n");
    
//    w.updateGL();
    
//    while(true){
//        if(tic_msg = messagelist["tic_inout"]->get()){
//            printLogFile("get tic \n");
//            _tic = static_cast<std::clock_t*>(tic_msg->data);
//            printLogFile("cur_tic : " + std::to_string(*_tic) + "\n");
//            delete _tic; // Освобождение области памяти *data
//            delete tic_msg; // Освобождение области памяти сообщения
//        }
//        else  std::this_thread::sleep_for(std::chrono::milliseconds(20));

    
//    	auxInitDisplayMode(AUX_RGB);
//	auxInitPosition (0, 0, 500, 500);
//	auxInitWindow ("Step1");
        
//        int argc = 1; 
//        typedef char** ppchar;
//        ppchar argv = reinterpret_cast<ppchar>(new char[2][10]);
//        argv = new *char[1];
//        argv[0] = "./Kate";
//        argv[1] = "";

//        char *argv_[] = {"./Kate",""};
//      
    
    
//    NSApplicationMain(mainargc, (const char **)mainargv);
//        printLogFile(std::to_string(mainargc) + "   " + mainargv[0] + "\n");
        
// QMessageBox msgBox;
// msgBox.setText("The document has been modified.");
// msgBox.exec();
        
//    }
    
};





/*
 
{
    Q_OBJECT
    Q_PROPERTY(QString objectName READ objectName WRITE setObjectName NOTIFY objectNameChanged)
    Q_DECLARE_PRIVATE(QObject)

public:
    Q_INVOKABLE explicit QObject(QObject *parent=0);
    virtual ~QObject();

    virtual bool event(QEvent *);
    virtual bool eventFilter(QObject *, QEvent *);

#ifdef Q_QDOC
    static QString tr(const char *sourceText, const char *comment = 0, int n = -1);
    static QString trUtf8(const char *sourceText, const char *comment = 0, int n = -1);
    virtual const QMetaObject *metaObject() const;
    static const QMetaObject staticMetaObject;
#endif
#ifdef QT_NO_TRANSLATION
    static QString tr(const char *sourceText, const char * = 0, int = -1)
        { return QString::fromUtf8(sourceText); }
#if QT_DEPRECATED_SINCE(5, 0)
    QT_DEPRECATED static QString trUtf8(const char *sourceText, const char * = 0, int = -1)
        { return QString::fromUtf8(sourceText); }
#endif
#endif //QT_NO_TRANSLATION

    QString objectName() const;
    void setObjectName(const QString &name);

    inline bool isWidgetType() const { return d_ptr->isWidget; }
    inline bool isWindowType() const { return d_ptr->isWindow; }

    inline bool signalsBlocked() const { return d_ptr->blockSig; }
    bool blockSignals(bool b);

    QThread *thread() const;
    void moveToThread(QThread *thread);

    int startTimer(int interval, Qt::TimerType timerType = Qt::CoarseTimer);
    void killTimer(int id);

    template<typename T>
    inline T findChild(const QString &aName = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
    {
        typedef typename QtPrivate::remove_cv<typename QtPrivate::remove_pointer<T>::type>::type ObjType;
        return static_cast<T>(qt_qFindChild_helper(this, aName, ObjType::staticMetaObject, options));
    }

    template<typename T>
    inline QList<T> findChildren(const QString &aName = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
    {
        typedef typename QtPrivate::remove_cv<typename QtPrivate::remove_pointer<T>::type>::type ObjType;
        QList<T> list;
        qt_qFindChildren_helper(this, aName, ObjType::staticMetaObject,
                                reinterpret_cast<QList<void *> *>(&list), options);
        return list;
    }

#ifndef QT_NO_REGEXP
    template<typename T>
    inline QList<T> findChildren(const QRegExp &re, Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
    {
        typedef typename QtPrivate::remove_cv<typename QtPrivate::remove_pointer<T>::type>::type ObjType;
        QList<T> list;
        qt_qFindChildren_helper(this, re, ObjType::staticMetaObject,
                                reinterpret_cast<QList<void *> *>(&list), options);
        return list;
    }
#endif

#ifndef QT_NO_REGULAREXPRESSION
    template<typename T>
    inline QList<T> findChildren(const QRegularExpression &re, Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
    {
        typedef typename QtPrivate::remove_cv<typename QtPrivate::remove_pointer<T>::type>::type ObjType;
        QList<T> list;
        qt_qFindChildren_helper(this, re, ObjType::staticMetaObject,
                                reinterpret_cast<QList<void *> *>(&list), options);
        return list;
    }
#endif

    inline const QObjectList &children() const { return d_ptr->children; }

    void setParent(QObject *);
    void installEventFilter(QObject *);
    void removeEventFilter(QObject *);

    static QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);

    static QMetaObject::Connection connect(const QObject *sender, const QMetaMethod &signal,
                        const QObject *receiver, const QMetaMethod &method,
                        Qt::ConnectionType type = Qt::AutoConnection);

    inline QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const char *member, Qt::ConnectionType type = Qt::AutoConnection) const;

#ifdef Q_QDOC
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, Functor functor);
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *context, Functor functor, Qt::ConnectionType type = Qt::AutoConnection);
#else
    //Connect a signal to a pointer to qobject member function
    template <typename Func1, typename Func2>
    static inline QMetaObject::Connection connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                     const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot,
                                     Qt::ConnectionType type = Qt::AutoConnection)
    {
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        typedef QtPrivate::FunctionPointer<Func2> SlotType;

        Q_STATIC_ASSERT_X(QtPrivate::HasQ_OBJECT_Macro<typename SignalType::Object>::Value,
                          "No Q_OBJECT in the class with the signal");

        //compilation error if the arguments does not match.
        Q_STATIC_ASSERT_X(int(SignalType::ArgumentCount) >= int(SlotType::ArgumentCount),
                          "The slot requires more arguments than the signal provides.");
        Q_STATIC_ASSERT_X((QtPrivate::CheckCompatibleArguments<typename SignalType::Arguments, typename SlotType::Arguments>::value),
                          "Signal and slot arguments are not compatible.");
        Q_STATIC_ASSERT_X((QtPrivate::AreArgumentsCompatible<typename SlotType::ReturnType, typename SignalType::ReturnType>::value),
                          "Return type of the slot is not compatible with the return type of the signal.");

        const int *types = 0;
        if (type == Qt::QueuedConnection || type == Qt::BlockingQueuedConnection)
            types = QtPrivate::ConnectionTypes<typename SignalType::Arguments>::types();

        return connectImpl(sender, reinterpret_cast<void **>(&signal),
                           receiver, reinterpret_cast<void **>(&slot),
                           new QtPrivate::QSlotObject<Func2, typename QtPrivate::List_Left<typename SignalType::Arguments, SlotType::ArgumentCount>::Value,
                                           typename SignalType::ReturnType>(slot),
                            type, types, &SignalType::Object::staticMetaObject);
    }

    //connect to a function pointer  (not a member)
    template <typename Func1, typename Func2>
    static inline typename QtPrivate::QEnableIf<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0, QMetaObject::Connection>::Type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)
    {
        return connect(sender, signal, sender, slot, Qt::DirectConnection);
    }

    //connect to a function pointer  (not a member)
    template <typename Func1, typename Func2>
    static inline typename QtPrivate::QEnableIf<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0 &&
                                                !QtPrivate::FunctionPointer<Func2>::IsPointerToMemberFunction, QMetaObject::Connection>::Type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, const QObject *context, Func2 slot,
                    Qt::ConnectionType type = Qt::AutoConnection)
    {
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        typedef QtPrivate::FunctionPointer<Func2> SlotType;

        Q_STATIC_ASSERT_X(QtPrivate::HasQ_OBJECT_Macro<typename SignalType::Object>::Value,
                          "No Q_OBJECT in the class with the signal");

        //compilation error if the arguments does not match.
        Q_STATIC_ASSERT_X(int(SignalType::ArgumentCount) >= int(SlotType::ArgumentCount),
                          "The slot requires more arguments than the signal provides.");
        Q_STATIC_ASSERT_X((QtPrivate::CheckCompatibleArguments<typename SignalType::Arguments, typename SlotType::Arguments>::value),
                          "Signal and slot arguments are not compatible.");
        Q_STATIC_ASSERT_X((QtPrivate::AreArgumentsCompatible<typename SlotType::ReturnType, typename SignalType::ReturnType>::value),
                          "Return type of the slot is not compatible with the return type of the signal.");

        const int *types = 0;
        if (type == Qt::QueuedConnection || type == Qt::BlockingQueuedConnection)
            types = QtPrivate::ConnectionTypes<typename SignalType::Arguments>::types();

        return connectImpl(sender, reinterpret_cast<void **>(&signal), context, 0,
                           new QtPrivate::QStaticSlotObject<Func2,
                                                 typename QtPrivate::List_Left<typename SignalType::Arguments, SlotType::ArgumentCount>::Value,
                                                 typename SignalType::ReturnType>(slot),
                           type, types, &SignalType::Object::staticMetaObject);
    }

    //connect to a functor
    template <typename Func1, typename Func2>
    static inline typename QtPrivate::QEnableIf<QtPrivate::FunctionPointer<Func2>::ArgumentCount == -1, QMetaObject::Connection>::Type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)
    {
        return connect(sender, signal, sender, slot, Qt::DirectConnection);
    }

    //connect to a functor, with a "context" object defining in which event loop is going to be executed
    template <typename Func1, typename Func2>
    static inline typename QtPrivate::QEnableIf<QtPrivate::FunctionPointer<Func2>::ArgumentCount == -1, QMetaObject::Connection>::Type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, const QObject *context, Func2 slot,
                    Qt::ConnectionType type = Qt::AutoConnection)
    {
#if defined (Q_COMPILER_DECLTYPE) && defined (Q_COMPILER_VARIADIC_TEMPLATES)
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        const int FunctorArgumentCount = QtPrivate::ComputeFunctorArgumentCount<Func2 , typename SignalType::Arguments>::Value;

        Q_STATIC_ASSERT_X((FunctorArgumentCount >= 0),
                          "Signal and slot arguments are not compatible.");
        const int SlotArgumentCount = (FunctorArgumentCount >= 0) ? FunctorArgumentCount : 0;
        typedef typename QtPrivate::FunctorReturnType<Func2, typename QtPrivate::List_Left<typename SignalType::Arguments, SlotArgumentCount>::Value>::Value SlotReturnType;
#else
      // Without variadic template, we don't detect the best overload of operator(). We just
      // assume there is only one simple operator() and connect to &Func2::operator()

      /* If you get an error such as:
             couldn't deduce template parameter 'Func2Operator'
        or
             cannot resolve address of overloaded function
        It means the functor does not have a single operator().
        Functors with overloaded or templated operator() are only supported if the compiler supports
        C++11 variadic templates
      */ /*
#ifndef Q_COMPILER_DECLTYPE  //Workaround the lack of decltype using another function as indirection
        return connect_functor(sender, signal, context, slot, &Func2::operator(), type); }
    template <typename Func1, typename Func2, typename Func2Operator>
    static inline QMetaObject::Connection connect_functor(const QObject *sender, Func1 signal, const QObject *context,
                                                          Func2 slot, Func2Operator, Qt::ConnectionType type) {
        typedef QtPrivate::FunctionPointer<Func2Operator> SlotType ;
#else
        typedef QtPrivate::FunctionPointer<decltype(&Func2::operator())> SlotType ;
#endif
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        typedef typename SlotType::ReturnType SlotReturnType;
        const int SlotArgumentCount = SlotType::ArgumentCount;

        Q_STATIC_ASSERT_X(int(SignalType::ArgumentCount) >= SlotArgumentCount,
                          "The slot requires more arguments than the signal provides.");
        Q_STATIC_ASSERT_X((QtPrivate::CheckCompatibleArguments<typename SignalType::Arguments, typename SlotType::Arguments>::value),
                          "Signal and slot arguments are not compatible.");
#endif

        Q_STATIC_ASSERT_X((QtPrivate::AreArgumentsCompatible<SlotReturnType, typename SignalType::ReturnType>::value),
                          "Return type of the slot is not compatible with the return type of the signal.");

        Q_STATIC_ASSERT_X(QtPrivate::HasQ_OBJECT_Macro<typename SignalType::Object>::Value,
                          "No Q_OBJECT in the class with the signal");

        const int *types = 0;
        if (type == Qt::QueuedConnection || type == Qt::BlockingQueuedConnection)
            types = QtPrivate::ConnectionTypes<typename SignalType::Arguments>::types();

        return connectImpl(sender, reinterpret_cast<void **>(&signal), context, 0,
                           new QtPrivate::QFunctorSlotObject<Func2, SlotArgumentCount,
                                typename QtPrivate::List_Left<typename SignalType::Arguments, SlotArgumentCount>::Value,
                                typename SignalType::ReturnType>(slot),
                           type, types, &SignalType::Object::staticMetaObject);
    }
#endif //Q_QDOC

    static bool disconnect(const QObject *sender, const char *signal,
                           const QObject *receiver, const char *member);
    static bool disconnect(const QObject *sender, const QMetaMethod &signal,
                           const QObject *receiver, const QMetaMethod &member);
    inline bool disconnect(const char *signal = 0,
                           const QObject *receiver = 0, const char *member = 0) const
        { return disconnect(this, signal, receiver, member); }
    inline bool disconnect(const QObject *receiver, const char *member = 0) const
        { return disconnect(this, 0, receiver, member); }
    static bool disconnect(const QMetaObject::Connection &);

#ifdef Q_QDOC
    static bool disconnect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method);
#else
    template <typename Func1, typename Func2>
    static inline bool disconnect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                  const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)
    {
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        typedef QtPrivate::FunctionPointer<Func2> SlotType;

        Q_STATIC_ASSERT_X(QtPrivate::HasQ_OBJECT_Macro<typename SignalType::Object>::Value,
                          "No Q_OBJECT in the class with the signal");

        //compilation error if the arguments does not match.
        Q_STATIC_ASSERT_X((QtPrivate::CheckCompatibleArguments<typename SignalType::Arguments, typename SlotType::Arguments>::value),
                          "Signal and slot arguments are not compatible.");

        return disconnectImpl(sender, reinterpret_cast<void **>(&signal), receiver, reinterpret_cast<void **>(&slot),
                              &SignalType::Object::staticMetaObject);
    }
    template <typename Func1>
    static inline bool disconnect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                  const QObject *receiver, void **zero)
    {
        // This is the overload for when one wish to disconnect a signal from any slot. (slot=0)
        // Since the function template parameter cannot be deduced from '0', we use a
        // dummy void ** parameter that must be equal to 0
        Q_ASSERT(!zero);
        typedef QtPrivate::FunctionPointer<Func1> SignalType;
        return disconnectImpl(sender, reinterpret_cast<void **>(&signal), receiver, zero,
                              &SignalType::Object::staticMetaObject);
    }
#endif //Q_QDOC


    void dumpObjectTree();
    void dumpObjectInfo();

#ifndef QT_NO_PROPERTIES
    bool setProperty(const char *name, const QVariant &value);
    QVariant property(const char *name) const;
    QList<QByteArray> dynamicPropertyNames() const;
#endif // QT_NO_PROPERTIES

#ifndef QT_NO_USERDATA
    static uint registerUserData();
    void setUserData(uint id, QObjectUserData* data);
    QObjectUserData* userData(uint id) const;
#endif // QT_NO_USERDATA

Q_SIGNALS:
    void destroyed(QObject * = 0);
    void objectNameChanged(const QString &objectName
#if !defined(Q_QDOC)
    , QPrivateSignal
#endif
    );

public:
    inline QObject *parent() const { return d_ptr->parent; }

    inline bool inherits(const char *classname) const
        { return const_cast<QObject *>(this)->qt_metacast(classname) != 0; }

public Q_SLOTS:
    void deleteLater();

protected:
    QObject *sender() const;
    int senderSignalIndex() const;
    int receivers(const char* signal) const;
    bool isSignalConnected(const QMetaMethod &signal) const;

    virtual void timerEvent(QTimerEvent *);
    virtual void childEvent(QChildEvent *);
    virtual void customEvent(QEvent *);

    virtual void connectNotify(const QMetaMethod &signal);
    virtual void disconnectNotify(const QMetaMethod &signal);

protected:
    QObject(QObjectPrivate &dd, QObject *parent = 0);

protected:
    QScopedPointer<QObjectData> d_ptr;

    static const QMetaObject staticQtMetaObject;

    friend struct QMetaObject;
    friend struct QMetaObjectPrivate;
    friend class QMetaCallEvent;
    friend class QApplication;
    friend class QApplicationPrivate;
    friend class QCoreApplication;
    friend class QCoreApplicationPrivate;
    friend class QWidget;
    friend class QThreadData;

private:
    Q_DISABLE_COPY(QObject)
    Q_PRIVATE_SLOT(d_func(), void _q_reregisterTimers(void *))

private:
    static QMetaObject::Connection connectImpl(const QObject *sender, void **signal,
                                               const QObject *receiver, void **slotPtr,
                                               QtPrivate::QSlotObjectBase *slot, Qt::ConnectionType type,
                                               const int *types, const QMetaObject *senderMetaObject);

    static bool disconnectImpl(const QObject *sender, void **signal, const QObject *receiver, void **slot,
                               const QMetaObject *senderMetaObject);

};
 
 
 
 */


