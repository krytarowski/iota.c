/*
 * Copyright (c) 2019 IOTA Stiftung
 * https://github.com/iotaledger/iota.c
 *
 * Refer to the LICENSE file for licensing information
 */

#include "cclient/api/tests/cclient_test_defs.h"

static iota_client_service_t *g_serv;

static void test_get_node_api_conf(void) {
  get_node_api_conf_res_t node_conf = {};
  TEST_ASSERT(node_conf.max_find_transactions == 0);
  TEST_ASSERT(node_conf.max_requests_list == 0);
  TEST_ASSERT(node_conf.max_get_trytes == 0);
  TEST_ASSERT(node_conf.max_body_length == 0);
  TEST_ASSERT(node_conf.milestone_start_index == 0);
  TEST_ASSERT(node_conf.test_net == false);

  TEST_ASSERT_EQUAL_INT16(RC_OK, iota_client_get_node_api_conf(g_serv, &node_conf));
  TEST_ASSERT(node_conf.max_find_transactions > 0);
  TEST_ASSERT(node_conf.max_requests_list > 0);
  TEST_ASSERT(node_conf.max_get_trytes > 0);
  TEST_ASSERT(node_conf.max_body_length > 0);
  TEST_ASSERT(node_conf.milestone_start_index > 0);
#ifdef IOTA_MAIN_NET
  TEST_ASSERT(node_conf.test_net == false);
#else
  TEST_ASSERT(node_conf.test_net == true);
#endif
}

int main() {
  UNITY_BEGIN();

  g_serv = cclient_service_setup();
  TEST_ASSERT_NOT_NULL(g_serv);

  RUN_TEST(test_get_node_api_conf);

  cclient_service_cleanup(&g_serv);
  TEST_ASSERT_NULL(g_serv);

  return UNITY_END();
}
