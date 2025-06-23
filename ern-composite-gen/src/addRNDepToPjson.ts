import { readPackageJson, writePackageJson } from 'ern-core';
import semver from 'semver';

export async function addRNDepToPjson(dir: string, version: string) {
  const compositePackageJson = await readPackageJson(dir);
  compositePackageJson.dependencies['react-native'] = version;

  // For React Native 0.73+, also add @react-native/metro-config dependency
  // This is required by the new Metro config format
  if (semver.gte(version, '0.73.0')) {
    compositePackageJson.dependencies['@react-native/metro-config'] = version;
  }

  return writePackageJson(dir, compositePackageJson);
}