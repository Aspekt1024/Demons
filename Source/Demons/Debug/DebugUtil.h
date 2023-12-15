#pragma once

#define DebugLog(message) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT(message));}