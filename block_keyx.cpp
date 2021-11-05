#include <znc/Modules.h>
#include <znc/User.h>
#include <znc/IRCNetwork.h>

class CFred : public CModule {
public:
        MODCONSTRUCTOR(CFred) {}

        virtual EModRet OnPrivNotice(CNick& Nick, CString& sMessage) {
                if (m_pNetwork->GetClients().empty() && sMessage.Token(0) == "DH1080_INIT") {
                        CString sPre, sPost;

                        sPre = ":" + GetModNick() + "!" + GetModName() + "@znc.in PRIVMSG ";

                        sPost = "Blocked DH1080_INIT from " + Nick.GetNickMask();
                        sPost = " :" + m_pUser->AddTimestamp(sPost);

                        m_pNetwork->AddRawBuffer(sPre, sPost);
                        return HALT;
                }
                return CONTINUE;
        }
};

MODULEDEFS(CFred, "Blocks/Logs Fish-KeyX if no Client connected")
