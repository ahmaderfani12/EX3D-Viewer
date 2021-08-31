#ifndef SETTINGDATA_H
#define SETTINGDATA_H


	class SettingData {
	public:

		static float skyColor[3];
		static float lightColor[3];
		static float lightShadowColor[3];
		static float rimColor[3];

		static float lightPosition[3];

		static float specular;
		static float specularPower;
		static float rimPower;
		static float rimStrength;

		static bool showGizmo;
	};

#endif