// Copyright 2019 Autodesk, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include <ai_nodes.h>

#include <pxr/usd/usd/prim.h>

#include <string>
#include <unordered_map>
#include <vector>

class UsdArnoldPrimReader;

PXR_NAMESPACE_USING_DIRECTIVE

/**
 *  This Registry stores which UsdArnoldPrimReader must be used to read a
 *UsdPrim of a given type. In its constructor, it will iterate over all known
 *arnold node types and register the corresponding UsdArnoldPrimReaders. This
 *class can be derived if we need to customize the list of prim readers to be
 *used
 **/

class UsdArnoldReaderRegistry {
public:
    UsdArnoldReaderRegistry();
    virtual ~UsdArnoldReaderRegistry();

    // Register a new prim reader to this type of usd primitive.
    // If an existing one was previously registed for this same type, it will be
    // deleted and overridden
    void registerReader(const std::string &primName, UsdArnoldPrimReader *primReader);

    UsdArnoldPrimReader *getPrimReader(const std::string &primName)
    {
        std::unordered_map<std::string, UsdArnoldPrimReader *>::iterator it = _readersMap.find(primName);
        if (it == _readersMap.end()) {
            return NULL; // return NULL if no reader was registered for this
                         // node type, it will be skipped
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, UsdArnoldPrimReader *> _readersMap;
};
