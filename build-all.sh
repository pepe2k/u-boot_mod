#!/bin/sh

ALL="8devices_carambola2 alfa-network_ap121f alfa-network_hornet-ub alfa-network_n5q alfa-network_r36a alfa-network_tube2h creatcomm-technology_d3321 dragino_ms14 engenius_ens202ext gainstrong_oolite_v1_dev gainstrong_oolite_v5.2 gainstrong_oolite_v5.2_dev gl-inet_6416 gl-inet_gl-ar150 gl-inet_gl-ar300 gl-inet_gl-ar300m-lite gl-inet_gl-ar750 gl-inet_gl-usb150 hak5_lan-turtle hak5_packet-squirrel hak5_wifi-pineapple-nano p2w_cpe505n p2w_r602n tp-link_eap245_v1 tp-link_tl-mr10u_v1 tp-link_tl-mr13u_v1 tp-link_tl-mr22u_v1 tp-link_tl-mr3020_v1 tp-link_tl-mr3040_v1v2 tp-link_tl-mr3220_v2 tp-link_tl-mr3420_v2 tp-link_tl-mr3420_v3 tp-link_tl-mr6400_v1v2 tp-link_tl-wa801nd_v2 tp-link_tl-wa830re_v2 tp-link_tl-wa850re_v2 tp-link_tl-wdr3500_v1 tp-link_tl-wdr3600_v1 tp-link_tl-wdr43x0_v1 tp-link_tl-wr1041n_v2 tp-link_tl-wr703n_v1 tp-link_tl-wr710n_v1 tp-link_tl-wr720n_v3_CN tp-link_tl-wr740n_v4 tp-link_tl-wr802n_v1 tp-link_tl-wr810n_v1 tp-link_tl-wr810n_v2 tp-link_tl-wr820n_v1_CN tp-link_tl-wr841n_v10 tp-link_tl-wr841n_v11 tp-link_tl-wr841n_v8 tp-link_tl-wr841n_v9 tp-link_tl-wr842n_v3 tp-link_tl-wr902ac_v1 unwireddevices_unwired-one village-telco_mesh-potato_v2 wallys_dr531 whqx_e600gac_v2 whqx_e600g_v2 yuncore_ap90q yuncore_cpe830 yuncore_t830 zbtlink_zbt-we1526"

ALL_64="comfast_cf-e314n comfast_cf-e320n_v2 comfast_cf-e520n comfast_cf-e530n d-link_dir-505_a1 yuncore_cpe870"

for device in $ALL_64 $ALL
do
	mkdir -p bin
	make $* clean
	make $* $device > bin/$device.log 2>&1
done

