#ifndef MESSAGE_TEST_H__
#define MESSAGE_TEST_H__

#include "gloox/client.h"
#include "gloox/messagesessionhandler.h"
#include "gloox/messageeventhandler.h"
#include "gloox/messageeventfilter.h"
#include "gloox/chatstatehandler.h"
#include "gloox/chatstatefilter.h"
#include "gloox/connectionlistener.h"
#include "gloox/disco.h"
#include "gloox/message.h"
#include "gloox/gloox.h"
#include "gloox/lastactivity.h"
#include "gloox/loghandler.h"
#include "gloox/logsink.h"
#include "gloox/connectiontcpclient.h"
#include "gloox/connectionsocks5proxy.h"
#include "gloox/connectionhttpproxy.h"
#include "gloox/messagehandler.h"

using namespace gloox;

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "gloox"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#include <stdio.h>
#include <string>
#include <cstdio>   // [s]print[f]
#include <unistd.h> // sleep
#include <stdarg.h>
#include <sstream>
#include <cstring>

using namespace std;

class MessageTest : public MessageSessionHandler
    , ConnectionListener
    , LogHandler
    , MessageEventHandler
    , MessageHandler
    , ChatStateHandler
{
public:
    MessageTest(JNIEnv *env, jobject obj);
    virtual ~MessageTest();

    void Log(string log)
    {
        static jmethodID cb = NULL;
        jclass cls = m_env->GetObjectClass(m_obj);
        
        if (cb == NULL) {
            cb = m_env->GetMethodID(cls, "testCallback", "(Ljava/lang/String;)V");
            if (cb == NULL) return;
        }
        
        m_env->CallVoidMethod(m_obj, cb, m_env->NewStringUTF(log.c_str()));
    }
    
    void start()
    {
        
        JID jid( "test1@bypass" );
        j = new Client( jid, "1234" );
        
        ConnectionTCPClient* conn = new ConnectionTCPClient( j, j->logInstance(), "msg.iam0.com", 5223 );
        j->setConnectionImpl( conn );
        
        j->registerConnectionListener( this );
        j->registerMessageSessionHandler( this, 0 );
        j->disco()->setVersion( "messageTest", GLOOX_VERSION, "Linux" );
        j->disco()->setIdentity( "client", "bot" );
        j->disco()->addFeature( XMLNS_CHAT_STATES );
        //      StringList ca;
        //      ca.push_back( "/path/to/cacert.crt" );
        //      j->setCACerts( ca );
        
        j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );
        
        //
        // this code connects to a jabber server through a SOCKS5 proxy
        //
        //       ConnectionSOCKS5Proxy* conn = new ConnectionSOCKS5Proxy( j,
        //                                   new ConnectionTCP( j->logInstance(),
        //                                                      "sockshost", 1080 ),
        //                                   j->logInstance(), "example.net" );
        //       conn->setProxyAuth( "socksuser", "sockspwd" );
        //       j->setConnectionImpl( conn );
        
        //
        // this code connects to a jabber server through a HTTP proxy through a SOCKS5 proxy
        //
        //       ConnectionTCP* conn0 = new ConnectionTCP( j->logInstance(), "old", 1080 );
        //       ConnectionSOCKS5Proxy* conn1 = new ConnectionSOCKS5Proxy( conn0, j->logInstance(), "old", 8080 );
        //       conn1->setProxyAuth( "socksuser", "sockspwd" );
        //       ConnectionHTTPProxy* conn2 = new ConnectionHTTPProxy( j, conn1, j->logInstance(), "jabber.cc" );
        //       conn2->setProxyAuth( "httpuser", "httppwd" );
        //       j->setConnectionImpl( conn2 );
        
        
        if( j->connect( false ) )
        {
            ConnectionError ce = ConnNoError;
            while( ce == ConnNoError )
            {
                ce = j->recv();
            }
            
            LOGI("ce: %d", ce);
        }
        
        delete( j );
    }
    
    virtual void onConnect()
    {
        Log( "connected!!!\n" );
    }
    
    virtual void onDisconnect( ConnectionError e )
    {
        LOGI("message_test: disconnected: %d\n", e);
        
        if( e == ConnAuthenticationFailed )
        {
            LOGI("auth failed. reason: %d\n", j->authError());
        }
    }
    
    virtual bool onTLSConnect( const CertInfo& info )
    {
        time_t from( info.date_from );
        time_t to( info.date_to );
        
        
        LOGI( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n"
             "from: %s\nto: %s\n",
             info.status, info.issuer.c_str(), info.server.c_str(),
             info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
             info.compression.c_str(), ctime( &from ), ctime( &to ) );
        return true;
    }
    
    virtual void handleMessage( const Message& msg, MessageSession * /*session*/ )
    {
        LOGI( "type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
             msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str() );
        
        std::string re = "You said:\n> " + msg.body() + "\nI like that statement.";
        std::string sub;
        if( !msg.subject().empty() )
            sub = "Re: " +  msg.subject();
        
        m_messageEventFilter->raiseMessageEvent( MessageEventDisplayed );
        sleep( 1 );
        m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
        m_chatStateFilter->setChatState( ChatStateComposing );
        sleep( 2 );
        m_session->send( re, sub );
        
        if( msg.body() == "quit" )
            j->disconnect();
    }
    
    virtual void handleMessageEvent( const JID& from, MessageEventType event )
    {
        LOGI( "received event: %d from: %s\n", event, from.full().c_str());
    }
    
    virtual void handleChatState( const JID& from, ChatStateType state )
    {
        LOGI( "received state: %d from: %s\n", state, from.full().c_str() );
    }
    
    virtual void handleMessageSession( MessageSession *session )
    {
        LOGI( "got new session\n");
        // this example can handle only one session. so we get rid of the old session
        j->disposeMessageSession( m_session );
        m_session = session;
        m_session->registerMessageHandler( this );
        m_messageEventFilter = new MessageEventFilter( m_session );
        m_messageEventFilter->registerMessageEventHandler( this );
        m_chatStateFilter = new ChatStateFilter( m_session );
        m_chatStateFilter->registerChatStateHandler( this );
    }
    
    virtual void handleLog( LogLevel level, LogArea area, const std::string& message )
    {
        LOGI( "log: level: %d, area: %d, %s\n", level, area, message.c_str());
    }
    
private:
    Client *j;
    MessageSession *m_session;
    MessageEventFilter *m_messageEventFilter;
    ChatStateFilter *m_chatStateFilter;
    JNIEnv *m_env;
    jobject m_obj;
};

#endif // MESSAGE_TEST_H__