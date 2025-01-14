#include "HttpHandler.h"
#include "Json.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"

UHttpHandler::UHttpHandler() {}

void UHttpHandler::SendAccountToBackend(const FString& Username, const FString& Email, const FString& DisplayName, TFunction<void(bool)> Callback)
{
    UE_LOG(LogTemp, Warning, TEXT("Sending account data to backend: %s, %s, %s"), *Username, *Email, *DisplayName);

    FString Url = TEXT("http://localhost:8080/createAccount");

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField(TEXT("username"), Username);
    JsonObject->SetStringField(TEXT("email"), Email);
    JsonObject->SetStringField(TEXT("display_name"), DisplayName);

    FString OutputString;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetContentAsString(OutputString);

    UE_LOG(LogTemp, Warning, TEXT("Sending HTTP POST request to %s"), *Url);

    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpHandler::OnCreateAccountResponse);
    HttpRequest->ProcessRequest();

    UE_LOG(LogTemp, Warning, TEXT("Request sent."));
}


void UHttpHandler::OnCreateAccountResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("Account created successfully!"));
      
        UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create account: %s"), *Response->GetContentAsString());
    }
}

