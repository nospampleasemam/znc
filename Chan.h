#ifndef _CHAN_H
#define _CHAN_H

#include "Nick.h"
#include <vector>
#include <map>
using std::vector;
using std::map;

// Forward Declarations
class CUser;
// !Forward Declarations

class CChan {
public:
	typedef enum {
		Private		= 1 << 0,
		Secret		= 1 << 1,
		NoMessages	= 1 << 2,
		Moderated	= 1 << 3,
		OpTopic		= 1 << 4,
		InviteOnly	= 1 << 5,
		Key			= 1 << 6
	} EMode;

	CChan(const CString& sName, CUser* pUser);
	virtual ~CChan();

	void Reset();
	void Joined();
	void Cycle() const;
	void JoinUser(bool bForce = false);
	void DetachUser();
	void SendBuffer();

	void IncClientRequests();
	bool DecClientRequests();

	bool Who();
	void OnWho(const CString& sNick, const CString& sIdent, const CString& sHost);

	// Modes
	void SetModes(const CString& s);
	void ModeChange(const CString& sModes, const CString& sNick = "");
	void OnOp(const CString& sOpNick, const CString& sNick, bool bOpped);
	void OnVoice(const CString& sOpNick, const CString& sNick, bool bVoiced);
	CString GetModeCString() const;
	CString GetModeArg(CString& sArgs) const;
	// !Modes

	// Nicks
	void ClearNicks();
	CNick* FindNick(const CString& sNick) const;
	int AddNicks(const CString& sNicks);
	bool AddNick(const CString& sNick);
	bool RemNick(const CString& sNick);
	bool ChangeNick(const CString& sOldNick, const CString& sNewNick);
	// !Nicks

	// Buffer
	int AddBuffer(const CString& sLine);
	void ClearBuffer();
	// !Buffer

	// Setters
	void SetIsOn(bool b) { m_bIsOn = b; if (!b) { Reset(); } else { Joined(); } }
	void SetOpped(bool b) { m_bIsOp = b; }
	void SetVoiced(bool b) { m_bIsVoice = b; }
	void SetKey(const CString& s) { m_sKey = s; }
	void SetTopic(const CString& s) { m_sTopic = s; }
	void SetTopicOwner(const CString& s) { m_sTopicOwner = s; }
	void SetTopicDate(unsigned long u) { m_ulTopicDate = u; }
	void SetDefaultModes(const CString& s) { m_sDefaultModes = s; }
	void IncOpCount() { m_uOpCount++; }
	void DecOpCount() { m_uOpCount -= (m_uOpCount > 0); }
	void IncVoiceCount() { m_uVoiceCount++; }
	void DecVoiceCount() { m_uVoiceCount -= (m_uVoiceCount > 0); }
	void SetBufferCount(unsigned int u) { m_uBufferCount = u; }
	void SetKeepBuffer(bool b) { m_bKeepBuffer = b; }
	void SetAutoCycle(bool b) { m_bAutoCycle = b; }
	void SetWhoDone(bool b = true) { m_bWhoDone = b; }
	void SetDetached(bool b = true) { m_bDetached = b; }
	// !Setters

	// Getters
	const bool IsOn() const { return m_bIsOn; }
	const bool IsOp() const { return m_bIsOp; }
	const bool IsVoice() const { return m_bIsVoice; }
	const CString& GetName() const { return m_sName; }
	unsigned int GetModes() const { return m_uModes; }
	const CString& GetKey() const { return m_sKey; }
	unsigned int GetLimit() const { return m_uLimit; }
	const CString& GetTopic() const { return m_sTopic; }
	const CString& GetTopicOwner() const { return m_sTopicOwner; }
	unsigned int GetTopicDate() const { return m_ulTopicDate; }
	const CString& GetDefaultModes() const { return m_sDefaultModes; }
	const vector<CString>& GetBans() const { return m_vsBans; }
	const vector<CString>& GetBuffer() const { return m_vsBuffer; }
	const map<CString,CNick*>& GetNicks() const { return m_msNicks; }
	unsigned int GetNickCount() const { return m_msNicks.size(); }
	unsigned int GetOpCount() const { return m_uOpCount; }
	unsigned int GetVoiceCount() const { return m_uVoiceCount; }
	unsigned int GetBufferCount() const { return m_uBufferCount; }
	bool HasMode(EMode eMode) const { return (m_uModes & eMode); }
	bool KeepBuffer() const { return m_bKeepBuffer; }
	bool AutoCycle() const { return m_bAutoCycle; }
	bool IsDetached() const { return m_bDetached; }
	// !Getters
private:
protected:
	bool				m_bDetached;
	bool				m_bIsOn;
	bool				m_bIsOp;
	bool				m_bIsVoice;
	bool				m_bWhoDone;
	bool				m_bKeepBuffer;
	bool				m_bAutoCycle;
	CString				m_sName;
	CString				m_sKey;
	CString				m_sTopic;
	CString				m_sTopicOwner;
	unsigned long		m_ulTopicDate;
	CUser*				m_pUser;
	unsigned int		m_uLimit;
	unsigned int		m_uModes;
	CString				m_sDefaultModes;
	vector<CString>		m_vsBans;
	map<CString,CNick*>	m_msNicks;	// Todo: make this caseless (irc style)
	unsigned int		m_uBufferCount;
	unsigned int		m_uOpCount;
	unsigned int		m_uVoiceCount;
	unsigned int		m_uClientRequests;	// Used to tell how many times a client tried to join this chan
	vector<CString>		m_vsBuffer;
};

#endif // !_CHAN_H
