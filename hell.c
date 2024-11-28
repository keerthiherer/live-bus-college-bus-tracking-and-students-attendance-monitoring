#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to connect to
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/api/index/");

        // Set the path to the CA certificate (Download cacert.pem)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\curl\\bin\\cacert.pem");

        // Optionally, disable SSL verification (For debugging only)
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Enable verbose output for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Curl initialization failed!\n");
    }

    curl_global_cleanup();
    int c;
    scanf("%d",&c);
    return 0;
}
