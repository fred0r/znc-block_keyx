#include <znc/Modules.h>
#include <znc/User.h>
#include <znc/IRCNetwork.h>
#include <znc/Query.h>

class CBlockKeyX : public CModule {
public:
        MODCONSTRUCTOR(CBlockKeyX) {}

        EModRet OnPrivNotice(CNick& Nick, CString& sMessage) override {
                if (m_pNetwork->GetClients().empty() && (sMessage.Token(0) == "DH1080_INIT" || sMessage.Token(0) == "DH1080_FINISH")) {
                        CQuery* pQuery = m_pNetwork->AddQuery(Nick.GetNick());
                        pQuery->AddBuffer(
                                ":" + GetModNick() + "!" + GetModName() + "@znc.in PRIVMSG " + _NAMEDFMT(Nick.GetNick()) + " :{text}",
                                "Blocked " + sMessage.Token(0) + " from " + Nick.GetNickMask());
                        return HALT;
                }
                return CONTINUE;
        }
};

MODULEDEFS(CBlockKeyX, "Blocks/Logs Fish-KeyX if no Client connected")
