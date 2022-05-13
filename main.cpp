#include <iostream>
#include <cpr/cpr.h>
#include "tidy.h"
#include "tidybuffio.h"

int main() {

    auto target_url = "https://www.vanticatrading.com/post/germany-crypto-held-for-more-than-a-year-will-not-get-taxed";
    cpr::Response r = cpr::Get(cpr::Url{target_url});

    TidyDoc tidyDoc = tidyCreate();
    TidyBuffer tidyOutputBuffer = {0};
    tidyOptSetBool(tidyDoc, TidyXmlOut, yes)
    && tidyOptSetBool(tidyDoc, TidyQuiet, yes)
    && tidyOptSetBool(tidyDoc, TidyNumEntities, yes)
    && tidyOptSetInt(tidyDoc, TidyCustomTags, TidyCustomEmpty)

    && tidyOptSetBool(tidyDoc, TidyShowWarnings, no)
    && tidyOptSetInt(tidyDoc, TidyWrapLen, 0);

    tidyParseString(tidyDoc, r.text.c_str());
    tidyCleanAndRepair(tidyDoc);
    tidySaveBuffer(tidyDoc, &tidyOutputBuffer);
    if (tidyOutputBuffer.bp) {
        std::string tidyResult;
        tidyResult = (char *) tidyOutputBuffer.bp;
        tidyBufFree(&tidyOutputBuffer);
//            pugi::xml_document xmlDoc;
//            // load_buffer() makes a copy of xml data
//            pugi::xml_parse_result result = xmlDoc.load_buffer(tidyResult.c_str(), tidyResult.size());

    }
    tidyRelease(tidyDoc);


    return 0;
}
