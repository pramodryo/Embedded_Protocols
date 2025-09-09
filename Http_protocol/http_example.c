#include <stdio.h>
#include <curl/curl.h>

// Callback function to write received data
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) 
{
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, stdout);  // Print to stdout
    return total_size;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize easy session
    curl = curl_easy_init();
    if(curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");

        // Follow redirections, if any
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Set callback function to handle response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the request
        res = curl_easy_perform(curl);

        // Error check
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Global libcurl cleanup
    curl_global_cleanup();

    return 0;
}

// compilation: gcc -o http http.c -lcurl
//./http

