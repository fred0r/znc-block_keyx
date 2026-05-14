#include <znc/Modules.h>
#include <znc/User.h>
#include <znc/IRCNetwork.h>
#include <znc/Query.h>

class CBlockKeyX : public CModule {
public:
        MODCONSTRUCTOR(CBlockKeyX) {}

        EModRet OnPrivNotice(CNick& Nick, CString& sMessage) override {
                if (!m_pNetwork->GetClients().empty())
                        return CONTINUE;

                CString sKey = sMessage.Token(0);
                if (sKey != "DH1080_INIT" && sKey != "DH1080_FINISH")
                        return CONTINUE;

                CQuery* pQuery = m_pNetwork->AddQuery(Nick.GetNick());
                pQuery->AddBuffer(
                        ":" + GetModNick() + "!" + GetModName() + "@znc.in PRIVMSG " + _NAMEDFMT(Nick.GetNick()) + " :{text}",
                        "Blocked " + sKey + " from " + Nick.GetNickMask());
                return HALT;
        }
};

template <>
void TModInfo<CBlockKeyX>(CModInfo& Info) {
    Info.SetWikiPage("block_keyx");
}

MODULEDEFS(CBlockKeyX,
           "Blocks/Logs Fish-KeyX if no Client connected")
