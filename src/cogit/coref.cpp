#include "coref.h"

CoRef::CoRef(CoRepo* repo, QString name, CoCommit* commit)
{
	m_repo = repo;
	m_name = name;
	m_commit = commit;
}
CoRef::CoRef(CoRepo* repo, QString name, QString commit)
{
	m_repo = repo;
	m_name = name;
	m_commit = new CoCommit(repo, commit);
}	
CoRef::CoRef(CoRepo* repe, QString name)
{
	m_repo = repo;
	m_name = name;
	//TODO
}
const QString CoRef::name() const
{
	return m_name;
}
bool setCommit(CoCommit* commit)
{
	m_commit = commit;
	if(m_commit == NULL)return false;
	return true;
}
bool setCommit(QString commit)
{
	//TODO
}
