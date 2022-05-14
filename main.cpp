#include <iostream>
#include <cpr/cpr.h>
#include "tidy.h"
#include "tidybuffio.h"

int main() {

//    auto target_url = "https://www.vanticatrading.com/post/germany-crypto-held-for-more-than-a-year-will-not-get-taxed";
//    cpr::Response r = cpr::Get(cpr::Url{target_url});
//
    auto htmlSample = "<html lang=\"en\" class=\"enable-scroll\"><head>"
                      "  <meta charset=\"utf-8\">\n"
                      "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" id=\"wixDesktopViewport\">\n"
                      "  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
                      "  <meta name=\"generator\" content=\"Wix.com Website Builder\">";
    "</head><body>";

    auto ss = std::ostringstream{};
    std::ifstream input_file("html.html");
    if (!input_file.is_open()) {
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();

    auto input = ss.str();

    TidyDoc tidyDoc = tidyCreate();
    TidyBuffer tidyOutputBuffer = {0};
    tidyOptSetBool(tidyDoc, TidyXmlOut, yes) &&
    tidyOptSetBool(tidyDoc, TidyQuiet, yes)
    && tidyOptSetBool(tidyDoc, TidyNumEntities, yes)

    && tidyOptSetBool(tidyDoc, TidyShowWarnings, no)
    &&      tidyOptSetInt(tidyDoc, TidyUseCustomTags, TidyCustomEmpty)
    ;

    tidyParseString(tidyDoc, input.c_str());
//    tidyParseString(tidyDoc, r.text.c_str());
    tidyCleanAndRepair(tidyDoc);
    tidySaveBuffer(tidyDoc, &tidyOutputBuffer);
    if (tidyOutputBuffer.bp) {
        std::string tidyResult;
        tidyResult = (char *) tidyOutputBuffer.bp;
        tidyBufFree(&tidyOutputBuffer);

        std::cout << tidyResult.c_str();

    }
    tidyRelease(tidyDoc);


    return 0;
}
