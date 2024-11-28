#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, (char *)ptr);
    return size * nmemb;  // Return the number of bytes written
}

int main(void) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    char data[1024] = "";  // Buffer to hold the response

    // JSON data to send in the POST request body
    const char *json_data = "{\"log\": 12.0000, \"lat\": 23.0233}";

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL of the Django API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/api/data2/");

        // Set the HTTP headers to indicate JSON data
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set the POST data (JSON payload)
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

        // Set the headers for the request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

        // Perform the POST request
        res = curl_easy_perform(curl);

        // Check if the request was successful
        if (res != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(res));
        } else {
            // Print the server's response
            printf("Response: \n%s\n", data);
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
    int i;
    scanf("%d",&i);
    return 0;
}
