/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 */

#ifndef COMPLETE_H
#define COMPLETE_H

#include <functional>
#include <map>

#include "coloredkdbio.hpp"
#include <command.hpp>
#include <kdb.hpp>

class CompleteCommand : public Command
{

public:
	CompleteCommand ();
	~CompleteCommand ();

	virtual std::string getShortOptions () override
	{
		return "dmMv0";
	}

	virtual std::string getSynopsis () override
	{
		return "<path>";
	}

	virtual std::string getShortHelpText () override
	{
		return "Show suggestions how the current name could be completed.";
	}

	virtual std::string getLongHelpText () override
	{
		return "Suggestions will include existing key names, path segments of existing key names and mountpoints.\n"
		       "Additionally, the output will indicate wheter the given path is a node or a leaf in the hierarchy of keys.";
	}

	virtual int execute (const Cmdline & cmdline) override;

private:
	void addMountpoints (kdb::KeySet & ks, const kdb::Key root);
	void addNamespaces (std::map<kdb::Key, std::pair<int, int>> & hierarchy);
	const std::map<kdb::Key, std::pair<int, int>> analyze (const kdb::KeySet & ks, const kdb::Key root, kdb::KeySet & virtualKeys,
							       const Cmdline & cmdLine);
	const kdb::Key getParentKey (const kdb::Key key);
	void increaseCount (std::map<kdb::Key, std::pair<int, int>> & hierarchy, const kdb::Key key,
			    const std::function<int(int)> depthIncreaser);
	void printResults (const std::string originalInput, const kdb::Key originalRoot, const kdb::Key root,
			   const std::map<kdb::Key, std::pair<int, int>> & hierarchy, const kdb::KeySet & virtualKeys,
			   const Cmdline & cmdLine);
	void printResult (const std::pair<kdb::Key, std::pair<int, int>> & current, const bool verbose);
	const std::function<bool(std::string)> determineFilterPredicate (const std::string originalInput, const kdb::Key originalRoot,
									 const kdb::Key root);
};

#endif
