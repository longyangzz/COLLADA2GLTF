#pragma once

#include "Dae.h"

#include <functional>
#include <list>
#include <map>
#include <string>

namespace opencollada
{
	class DaeValidator
	{
	public:
		DaeValidator(const std::list<std::string> & daePaths);

		int checkAll();
		int checkSchema(const std::string & schema_uri = std::string());
		int checkUniqueIds();
		int checkUniqueSids();
		int checkLinks();

	private:
		int checkSchema(const Dae & dae);
		int checkAll(const Dae & dae);
		int checkUniqueIds(const Dae & dae);
		int checkUniqueSids(const Dae & dae);
		int checkLinks(const Dae & dae);

		int for_each_dae(const std::function<int(const Dae &)> & task) const;

		static int ValidateAgainstSchema(const Dae & dae, const XmlSchema & schema);
		static int CheckEscapeChar(const std::string & s);

	private:
		std::vector<std::string> mDaePaths;
		// namespace to XmlSchema
		std::map<std::string, XmlSchema> mSchemas;
		// namespace to xsd location
		std::map<std::string, std::string> mSchemaLocations;
	};
}