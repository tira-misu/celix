/**
 *Licensed to the Apache Software Foundation (ASF) under one
 *or more contributor license agreements.  See the NOTICE file
 *distributed with this work for additional information
 *regarding copyright ownership.  The ASF licenses this file
 *to you under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in compliance
 *with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *Unless required by applicable law or agreed to in writing,
 *software distributed under the License is distributed on an
 *"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 *specific language governing permissions and limitations
 *under the License.
 */
/*
 * dependency_manager.c
 *
 *  \date       May 12, 2010
 *  \author    	<a href="mailto:celix-dev@incubator.apache.org">Apache Celix Project Team</a>
 *  \copyright	Apache License, Version 2.0
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dependency_manager.h"
#include "dependency_activator_base.h"
#include "bundle_context.h"
#include "service_component_private.h"

DEPENDENCY_MANAGER dependencyManager_create(bundle_context_t context) {
	DEPENDENCY_MANAGER manager = (DEPENDENCY_MANAGER) malloc(sizeof(*manager));
	apr_pool_t *pool = NULL;
	apr_pool_t *npool = NULL;
	bundleContext_getMemoryPool(context, &pool);
	apr_pool_create(&npool, pool);
	manager->context = context;
	manager->services = NULL;
	arrayList_create(npool, &manager->services);
	return manager;
}

void dependencyManager_add(DEPENDENCY_MANAGER manager, SERVICE service) {
	arrayList_add(manager->services, service);
	serviceComponent_start(service);
}

void dependencyManager_remove(DEPENDENCY_MANAGER manager, SERVICE service) {
	serviceComponent_stop(service);
	arrayList_removeElement(manager->services, service);
}

SERVICE dependencyManager_createService(DEPENDENCY_MANAGER manager) {
	return serviceComponent_create(manager->context, manager);
}

SERVICE_DEPENDENCY dependencyManager_createServiceDependency(DEPENDENCY_MANAGER manager) {
	return serviceDependency_create(manager->context);
}